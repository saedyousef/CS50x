#include <cs50.h>
#include <math.h>
#include <stdio.h>

    int main(void)
    {

        float dollars;
        int cents;
        int coins = 0;

        do{
            dollars = get_float("Change Owed:");

        }
        while (dollars <= 0 );
        cents = round(dollars * 100);
        while (cents > 0)
        {
            if (cents >= 25)
            {
                cents = cents - 25;
            }
            else if (cents >= 10)
            {
                cents = cents - 10;
            }
            else if (cents >= 5)
            {
                cents = cents - 5;
            }
            else {
                cents--;
            }
            coins++;
        }
        

        printf("%i\n", coins );

    }