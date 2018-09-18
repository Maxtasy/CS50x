#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    int change = 0;

    do
    {
        printf("Change owed: ");
        change = round(100 * get_float());
    }
    while (change < 0);

    int quarters = 0;
    int dimes = 0;
    int nickels = 0;
    int pennies = 0;

    while (change >= 25)
    {
        change -= 25;
        quarters++;
    }

    while (change >= 10)
    {
        change -= 10;
        dimes++;
    }

    while (change >= 5)
    {
        change -= 5;
        nickels++;
    }

    while (change >= 1)
    {
        change -= 1;
        pennies++;
    }

    int coins = quarters + dimes + nickels + pennies;

    printf("%i\n", coins);
}