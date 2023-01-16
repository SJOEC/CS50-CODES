#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main (void)
{
    char *s = get_string("s: ");

    /*
    se supone que queriamos copiar el string, pero solo estabamos copiando la direccion
    char *t = s;
    */

   char *t = malloc(strlen(s) + 1);
    /*
    for (int i = 0; i < strlen(s) + 1; i ++)
    {
        t[i] = s[i];
    }
    */
    // tecnicamente, hace lo mismo que el bucle
    strcpy(t, s);

    if (strlen(s) > 1)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);


    free(t);
}