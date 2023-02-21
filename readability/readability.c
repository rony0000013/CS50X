#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// prototyping the functions and creating global variable len
int len;
int count_letters(string words);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    len = strlen(text);
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    float index = 0.0588 * (letters / words * 100) - 0.296 * (sentences / words * 100) - 15.8;
    int idx = (int) round(index);

    if (idx < 1)        // printing the output
    {
        printf("Before Grade 1\n");
    }
    else if (idx >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", idx);
    }
}

int count_letters(string text)    //function to count letters
{
    int count = 0;

    for (int i = 0; i < len; i++)   // checks for letters
    {
        if (isalpha(text[i]))
        {
            count += 1;
        }
    }

    return count;
}

int count_words(string text)    //function to count words
{
    int count = 1;

    for (int i = 0; i < len; i++)   // checks for spaces
    {
        if ((int) text[i] == 32)
        {
            count += 1;
        }
    }

    return count;
}

int count_sentences(string text)    //function to count sentences
{
    int count = 0;

    for (int i = 0; i < len; i++)
    {
        if ((int) text[i] == 46 || (int) text[i] == 63 || (int) text[i] == 33)   // checks for . ? !
        {
            count += 1;
        }
    }

    return count;
}