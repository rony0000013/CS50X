#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int get_ascii(char c, int k);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc == 1 || argc > 2)
    {

        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Make sure every character in argv[1] is a digit
    int n = strlen(argv[1]);

    for (int i = 0; i < n; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int j = 0, k = 0;

    while (argv[1][j] && (argv[1][j] >= '0' && argv[1][j] <= '9'))
    {
        k = k * 10 + (argv[1][j] - '0');
        j++;
    }
    k = k % 26;

    // Prompt user for plaintext
    string text = get_string("plaintext: ");
    int len = strlen(text);
    char cipher[len];

    // For each character in the plaintext:
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            // Rotate the character if it's a letter
            cipher[i] = get_ascii(text[i], k);
        }
        else
        {
            cipher[i] = text[i];
        }
    }

    // print the output of cipher
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        printf("%c", cipher[i]);
    }
    printf("\n");

    return 0;
}

int get_ascii(char c, int k)        //get cipher text ascii
{
    int res = (int) c + k;

    if (islower(c))
    {
        return (res - 96) % 26 + 96;
    }
    else if (isupper(c))
    {
        return (res - 64) % 26 + 64;
    }

    return res;
}