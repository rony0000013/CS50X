#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // taking co-rrecct input from user
    int n = 0;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    //starting for loop for crrating pattern
    for (int i = 1; i <= n; i++)
    {

        //for loop for indentation
        for (int j = n - i - 1; j >= 0; j--)
        {
            printf(" ");
        }

        //for loop for left pattern
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        //middle gap
        printf("  ");

        //foor loop for right pattern
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        //creating new line after every row
        printf("\n");
    }

}