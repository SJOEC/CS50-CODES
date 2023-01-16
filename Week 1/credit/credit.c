#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long start_card = 0;
    long card = 0;
    int odds = 0;
    int evens = 0;
    int check = 0;
    int helper = 0;
    int len = 0;

    card = get_long("Number: ");

    start_card = card;

    //check the card
    for (int i = 0; i < 16; i++)
    {
        odds += card % 10;
        card /= 10;

        if ((card % 10 * 2) > 9)
        {
            // if the multiplication of the number has 2 digits, separate
            helper = (card % 10 * 2);
            // add one digit
            evens += helper % 10;
            helper /= 10;
            // add second digit
            evens += helper;
        }
        else
        {
            evens += (card % 10 * 2);
        }

        card /= 10;

    }
    /*
    printf("%i\n", odds);
    printf("%i\n", evens);
    */

    check = evens + odds;

    //check if the card is valid
    if (check % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // check for the card leght
    if (start_card >= 1000000000000)
    {
        len = 13;
    }
    if (start_card >= 10000000000000)
    {
        len = 14;
    }
    if (start_card >= 100000000000000)
    {
        len = 15;
    }
    if (start_card >= 1000000000000000)
    {
        len = 16;
    }

    // check for the starting digits
    for (int i = 0; i < (len - 2); i++)
    {
        start_card /= 10;
    }

    //check for the card type
    if (start_card == 34 || start_card == 37)
    {
        printf("AMEX\n");
        return 0;
    }
    else if (start_card >= 51 && start_card <= 55)
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else if ((start_card /= 10) == 4)
    {
        printf("VISA\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

}