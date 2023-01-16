#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    int cents = 0;

    do
    {
        cents = get_int("Give a number of cents: ");
    }
    while (cents <= 0);

    return cents;
}

int calculate_quarters(int cents)
{
    int quarters = 0;

    //calculate quarters
    for (int i = 0;; i++)
    {
        if (cents >= 25)
        {
            cents -= 25;
            quarters += 1;
        }
        else
        {
            break;
        }
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    int dimes = 0;

    //calculate dines
    for (int i = 0;; i++)
    {
        if (cents >= 10)
        {
            cents -= 10;
            dimes += 1;
        }
        else
        {
            break;
        }
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    int nickels = 0;

    //calculate nickels
    for (int i = 0;; i++)
    {

        if (cents >= 5)
        {
            cents -= 5;
            nickels += 1;
        }
        else
        {
            break;
        }

    }

    return nickels;
}

int calculate_pennies(int cents)
{
    int pennies = 0;

    //calculate pennies
    for (int i = 0;; i++)
    {
        if (cents >= 1)
        {
            cents -= 1;
            pennies += 1;
        }
        else
        {
            break;
        }
    }
    return pennies;
}