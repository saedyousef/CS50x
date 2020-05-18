#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Functions prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user to insert the text.
    string text = get_string("Text: ");

    // Functions calls.
    int L = count_letters(text);
    int W = count_words(text);
    int S = count_sentences(text);
    
    /** Testing
    printf("%d letter(s)\n", L);
    printf("%d word(s)\n", W);
    printf("%d sentence(s)\n", S);
    */

    // Calculate the readability grade/level.
    float level = 0.0588 * (100 * (float) L / (float) W) - 0.296 * (100 * (float) S / (float) W) - 15.8;

    // Checking for the grade.
    if (level < 16 && level >= 1)
    {
        printf("Grade %d\n", (int) round(level));
    }
    else if (level >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
    
    return 0;
}

// Count all alphabetical.
int count_letters(string text)
{
    // Initialize the count with value of 0.
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    
    return count;
}

// Count all wrods in the text.
int count_words(string text)
{
    // Initialize the count with value of 0.
    int count = 0;

    // To check if the next character is whitspace or an alpha (that's mean begging of a new word).
    bool isWord = true;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) && isWord)
        {
            count++;
            isWord = false;
        }
        if (text[i] == ' ')
        {
            isWord = true;
        }
    }
    
    return count;
}

// Count all sentences in the text.
int count_sentences(string text)
{
    // Initialize the count with value of 0.
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}