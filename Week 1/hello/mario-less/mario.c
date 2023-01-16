#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    // separate each line
    for (int i = 1; i <= height; i++)
    {
        //print spaces
        for (int j = 1; j <= height - i; j++)
        {
            printf(" ");

        }
        //print blocks
        for (int k = 0; k < i; k++)
        {
            printf("#");

        }
        //change row
        printf("\n");
    }
}