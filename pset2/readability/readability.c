#include <cs50.h>
#include <stdio.h>

// Functions prototypes
int count_letters(string text);

int main(void)
{
    // TODO
    string text = get_string("Text: \n");

    count_letters(text);
    
    return 0;
}

int count_letters(string text)
{
    return 1;
}