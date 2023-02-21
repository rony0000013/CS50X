#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

string key;
char get_cipher(char c);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    if (argc == 1 || argc > 2)
    {

        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Make sure key in argv[1] is a correct
    int n = strlen(argv[1]);

    if (n == 26)
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
            else
            {
                char item = tolower(argv[1][i]);
                int count = 0;
                for (int j = 0; j < 26; j++)
                {
                    if ((int) tolower(argv[1][j]) == (int) item)
                    {
                        count += 1;
                    }
                }

                if (count != 1)
                {
                    printf("Usage: ./substitution key\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    key = argv[1];

    // Prompt user for plaintext
    string text = get_string("plaintext: ");
    int len = strlen(text);
    char cipher[len];

    // For each character in the plaintext:
    for (int i = 0; i < len; i++)
    {
        cipher[i] = get_cipher(text[i]);
    }

    // Printing the output
    printf("ciphertext: ");
    for (int i = 0; i < len; i++)
    {
        printf("%c",cipher[i]);
    }
    printf("\n");

    return 0;

}

char get_cipher(char c)     // function to get cipher char from normal char
{
    if (isupper(c))
    {
        return toupper(key[((int) c) - 65]);
    }
    else if (islower(c))
    {
        return tolower(key[((int) c) - 97]);
    }

    return c;
}