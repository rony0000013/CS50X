# TODO
from cs50 import get_float

# getting height
n = get_float("Change owed: ")

# checking hright
while n < 0:
    n = get_float("Change owed: ")

n = n*100

x = int(n // 25)
n = n - (n // 25) * 25

y = int(n // 10)
n = n - (n // 10) * 10

z = int(n // 5)
n = n - (n // 5) * 5

change = int(n // 1)
change = change + x + y + z


print(change)
