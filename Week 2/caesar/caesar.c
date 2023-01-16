#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Load prototipes
bool only_digit(string digit);
char rotate(int k, char plaintext);

int main(int argc, string argv[])
{
    // check number of comand line arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string digit = argv[1];
    //check if is a digit
    if (only_digit(digit) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // get int from a string
    int k = atoi(argv[1]);

    //save plain text in a variable
    string plaintext = get_string("plaintext: ");

    //print ciphertext mesage
    printf("ciphertext: ");

    // print each char now cipher
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(k, plaintext[i]));
    }

    printf("\n");
}

bool only_digit(string digit)
{
    // if isnt a digit, kill the program

    for (int i = 0; i < strlen(digit); i++)
    {
        if (isdigit(digit[i]) == false)
        {
            return false;
        }
    }

    return true;
}

char rotate(int k, char plaintext)
{
    if (isupper(plaintext))
    {
        plaintext = (((int)plaintext - 65) + k) % 26;
        plaintext += 65;
    }
    else if (islower(plaintext))
    {
        plaintext = (((int)plaintext - 97) + k) % 26;
        plaintext += 97;
    }
    else
    {
        plaintext += 0;
    }

    return plaintext;
}