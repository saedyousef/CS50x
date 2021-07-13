#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

// Functions prototypes.
bool check_sum(long long card_number);

int main(void)
{
    // Prompt user to enter card number.
    long card_number = get_long("Number: ");
    
    // Check for card.
    if (card_number <= 0)
    {
        printf("INVALID\n");
        return 1;
    }

    // Check the checksum.
    if (!check_sum(card_number))
    {
        printf("INVALID\n");
        return 0;
    }

    return 0;
}

bool check_sum(long long card_number)
{
    long long digits = card_number;
    long long cc = digits;
    int count = 0;

    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }

    // Assign the card number into array.
    int numbers[count];
    int number[count];

    for (int i = 0; i < count; i++)
    {
        // Store the last digit.
        numbers[i] = cc % 10;
        number[i] = cc % 10;

        // Remove the last digit.
        cc = cc / 10;
    }

    // Splitting the card numbers into digits.
    for (int i = 1; i < count; i += 2)
    {
        number[i] = number[i] * 2;
    }
    
    int sum = 0;
    int multi;
    for (int i = 0; i < count; i++)
    {
        multi = (number[i] % 10) + (number[i] / 10 % 10);
        sum = sum + multi;
    }

    // If the last digit was 0 continue.
    if (sum % 10 == 0)
    {
        // Declaring the Cards numbers digits.
        int AMEX[] = {34, 37};
        int MasterCard[] = {51, 52, 53, 54, 55};
        int Visa = 4;

        // Concatenate the first two numbers.
        int digitsNumber = (numbers[count - 1] * 10) + numbers[count - 2];

        // Now checking for every card.
        if (count == 13 || count == 16)
        {
            if (numbers[count - 1] == Visa)
            {
                printf("VISA\n");
                return true;
            }
            else if (count == 16)
            {
                for (int i = 0; i < 5; i++)
                {
                    if (digitsNumber == MasterCard[i])
                    {
                        printf("MASTERCARD\n");
                        return true;
                    }
                }
            }        
        }
        else if (count == 15)
        {
            for (int i = 0; i < 2; i++)
            {
                if (digitsNumber == AMEX[i])
                {
                    printf("AMEX\n");
                    return true;
                }
            } 
        }
        
        return false;
    }
    
    return false;
}