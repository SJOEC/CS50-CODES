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

    for (int i = 1; i <= height; i++)
    {
        for (int j = 0; j < height - i; j ++)
        {
            // print space
            printf(" ");
        }
        for (int k = 0; k < i; k ++)
        {
            // print l-hashes
            printf("#");
        }
        for (int l = 0; l < 1; l++)
        {
            //print gap
            printf("  ");
        }
        for (int l = 0; l < i; l++)
        {
            //print r-hashes
            printf("#");
        }
        printf("\n");
    }
}