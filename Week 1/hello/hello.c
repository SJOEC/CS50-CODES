#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What's your name?\n");

    // The program says hello to the user
    printf("Hello, %s\n", name);

}
