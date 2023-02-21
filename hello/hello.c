#include <stdio.h>
#include <cs50.h>
int main(void)
{
    // getting input from users
    string name = get_string("What's your name? ");
    //printing the hello + input
    printf("hello, %s\n", name);
}