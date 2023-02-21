#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// creating checksum function
int chksum(int n, int arr[])
{
    int sum2 = 0;
    int sum1 = 0;
    if (n % 2 == 0) // sorting the array if size is even or odd
    {
        int temp = 0;
        for (int x = 0; x < n; x += 2) //for odd initializing 2 mult and sum
        {
            temp = arr[x] * 2;
            while (temp > 0)    //adding value to sum2
            {
                sum2 += temp % 10;
                temp /= 10;
            }
        }
        for (int x = 1; x < n; x += 2)  //adiing the remaining digit sum
        {
            sum1 += arr[x];
        }
    }
    else
    {
        int temp = 0;
        for (int x = 1; x < n; x += 2)      //for even initializing 2 mult and sum
        {
            temp = arr[x] * 2;
            while (temp > 0)    //adding value to sum2
            {
                sum2 += temp % 10;
                temp /= 10;
            }
        }
        for (int x = 0; x < n; x += 2)  //adiing the remaining digit sum
        {
            sum1 += arr[x];
        }
    }

    return ((sum1 + sum2) % 10 == 0) ? 1 : 0; //validiting the checksum
}

int main(void)
{

    long n = 0 ;
    //getting input from the user
    n = get_long("Number: ");

    const int ndigit = floor(log10(n)) + 1;     // counting the number of digits in number
    if (ndigit == 10) // if no of digit = 10 exit code
    {
        printf("INVALID\n");
        exit(0);
    }
    int arr[ndigit];

    // creating an array from the number
    for (int i = ndigit - 1; i >= 0; i--)
    {
        arr[i] = n % 10;
        n = n / 10;
    }

    //checking for validity and the category of card
    if (chksum(ndigit, arr))
    {
        if (arr[0] == 4 && (ndigit == 13 || ndigit == 16))
        {
            printf("VISA\n");
        }
        else if (arr[0] == 5 && ndigit == 16 && (arr[1] == 1 || arr[1] == 2 || arr[1] == 3 || arr[1] == 4 || arr[1] == 5))
        {
            printf("MASTERCARD\n");
        }
        else if (arr[0] == 3 && (arr[1] == 4 || arr[1] == 7) && ndigit == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}