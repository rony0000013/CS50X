# TODO
from cs50 import get_int

# getting height
n = get_int("Height: ")

# checking hright
while n < 1 or n > 8:
    n = get_int("Height: ")

# printing design
for i in range(1, n + 1):
    # printing whitespaces
    print(" " * (n - i), end="")

    print("#"*i, "", "#"*i)

