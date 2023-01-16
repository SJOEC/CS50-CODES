#include <stdio.h>

int main(void)
{

    char *hi_string = "HI!";


    for (int i = 0; i < 4; i++)
    {
        printf("%c\n", *(hi_string + i));
    }

}