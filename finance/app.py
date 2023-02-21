import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    balance = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]

    data = db.execute("SELECT stock, SUM(shares) as shares FROM transactions WHERE user = ? GROUP BY stock;", session["user_id"])

    if len(data) == 0:
        return render_template("index.html", data=None, total=balance, g_total=balance)

    g_total = balance
    for item in data:
        item["price"] = lookup(item["stock"])["price"]
        item["name"] = lookup(item["stock"])["name"]
        item["total"] = item["price"] * item["shares"]
        g_total += item["shares"] * item["price"]

    return render_template("index.html", data=data, total=balance, g_total=g_total)

def isInt(num):
    try:
        int(num)
        return True
    except:
        return False

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # checking for blank input
        if not request.form.get("symbol"):
            return apology("Symbol cannot be blank", 400)

        # Get quote from api using lookup function
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Lookup doesnot exists. Please enter valid lookup.", 400)

        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # shares not given or are invalid
        if not isInt(request.form.get("shares")):
            return apology("Entered Invalid stock numbers", 400)

        elif int((request.form.get("shares"))) <= 0:
            return apology("You cannot buy 0 stocks", 400)

        # Checking if user can buy the stock
        if quote["price"] * int(request.form.get("shares")) > float(balance):
            return apology("Insufficient Balance", 400)

        db.execute("INSERT INTO transactions (user, stock, shares, price, date_time) VALUES (?, ?, ?, ?, DATETIME('now'));", session["user_id"], request.form.get("symbol"), request.form.get("shares"), -(quote["price"] * int(request.form.get("shares"))))
        db.execute("UPDATE users SET cash = ? WHERE id = ?",balance - quote["price"] * int(request.form.get("shares")), session["user_id"])

        booked = "Bought " + quote["name"] + " at "
        booked_price = quote["price"] * int(request.form.get("shares"))
        balance = balance - quote["price"] * int(request.form.get("shares"))
        return render_template("buy.html", booked=booked, booked_price=booked_price, balance=balance)

    else:
        return render_template("buy.html", booked=None)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT * FROM transactions WHERE user = ?", session["user_id"])

    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # checking for correct lookup
        if not request.form.get("symbol"):
            return apology("Symbol cannot be blank", 400)

        # Get quote from api using lookup function
        quote = lookup(request.form.get("symbol"))

        if not quote:
            return apology("Lookup doesnot exists. Please enter valid lookup.", 400)

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # take and check username
        if not request.form.get("username"):
            return apology("must provide username", 400)

        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(row) != 0:
            return apology("username already exists retry with another", 400)

        # Take and check password
        if not request.form.get("password"):
            return apology("must provide password", 400)

        # Take and check password confirmation
        if not request.form.get("confirmation"):
            return apology("must provide matching password", 400)

        # check for not matching password
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords are not matching", 400)

        # Insert userdata to database and storing ID
        id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        # Remember which user has logged in
        session["user_id"] = id

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        items = []
        data = db.execute("SELECT stock, SUM(shares) as shares FROM transactions WHERE user = ? GROUP BY stock;", session["user_id"])

        for item in data:
            if item["shares"] != 0:
                items.append(item["stock"])

        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        # Get quote from api using lookup function
        quote = lookup(request.form.get("symbol"))

        for item in data:
            if item["stock"] == request.form.get("symbol"):
                shares = item["shares"]

        # shares not given or are invalid
        if not isInt(request.form.get("shares")):
            return apology("Entered Invalid stock numbers", 400)

        elif int((request.form.get("shares"))) <= 0:
            return apology("You cannot buy 0 stocks", 400)

        # checks if user has that many stocks
        if shares < int(request.form.get("shares")):
            return apology("User Doesnot own that many shares", 400)

        # Update the DataBase
        db.execute("INSERT INTO transactions (user, stock, shares, price, date_time) VALUES (?, ?, ?, ?, DATETIME('now'));", session["user_id"], request.form.get("symbol"), -int(request.form.get("shares")), quote["price"] * int(request.form.get("shares")))
        db.execute("UPDATE users SET cash = ? WHERE id = ?",balance + quote["price"] * int(request.form.get("shares")), session["user_id"])

        sold = "Sold " + quote["name"] + " at "
        sold_price = quote["price"] * int(request.form.get("shares"))
        balance = balance + quote["price"] * int(request.form.get("shares"))

        return render_template("sell.html", sold=sold, sold_price=sold_price, balance=balance, items=items)

    else:
        items = []
        data = db.execute("SELECT stock, SUM(shares) as shares FROM transactions WHERE user = ? GROUP BY stock;", session["user_id"])

        for item in data:
            if item["shares"] != 0:
                items.append(item["stock"])

        return render_template("sell.html", sold=None, items=items)
