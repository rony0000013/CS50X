# TODO
from cs50 import get_string
import re
import sys


def main():
    num = get_string("Number: ")
    n = len(num)    # counting the number of digits in number

    # if no of digit = 10 exit code
    if n <= 10:
        print("INVALID")
        sys.exit(0)

    # checking for validity and the category of card
    if chksum(num):

        if re.search(r'^4', num) and (n == 13 or n == 16):
            print("VISA")

        elif re.search(r'^5[1-5]', num) and n == 16:
            print("MASTERCARD")

        elif re.search(r'^3[47]', num) and n == 15:
            print("AMEX")

        else:
            print("INVALID")
    else:
        print("INVALID")


def chksum(num):
    sum1, sum2, n = 0, 0, len(num)
    arr = list(map(int, num))

    # sorting the array if size is even or odd
    if n % 2 == 0:
        temp = 0

        # for odd initializing 2 mult and sum
        for x in range(0, n, 2):
            temp = arr[x] * 2
            # adding value to sum2
            while temp > 0:
                sum2 += temp % 10
                temp = temp // 10

        # adiing the remaining digit sum
        for x in range(1, n, 2):
            sum1 += arr[x]

    else:
        temp = 0
        # for even initializing 2 mult and sum
        for x in range(1, n, 2):
            temp = arr[x] * 2
            # adding value to sum2
            while temp > 0:
                sum2 += temp % 10
                temp = temp // 10

        # adiing the remaining digit sum
        for x in range(0, n, 2):
            sum1 += arr[x]

    # validiting the checksum
    return True if (sum1 + sum2) % 10 == 0 else False


main()