#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


bool keyValidation(string key, int keyLength);
string encryptText(string plainText, string key);

int main(int argc, string argv[])
{
    // Check if the user has passed the key arg. or not.
    if(argc != 2)
    {
        printf("Usage : ./substitution key");
        return 1;
    }

    string key = argv[1];
    int keyLength = strlen(key);

    // Validate the key as required.
    bool valid = keyValidation(key, keyLength);

    if(!valid)
    {
        return 1;
    }

    string plainText = get_string("Plain text: ");
}

bool keyValidation(string key, int keyLength)
{
    // Check if the key contains numbers or special characters.
    for(int i = 0; i < keyLength; i++)
    {
        if(!isalpha(key[i]))
        {
            printf("Usage : ./substitution key");
            return false;
        }
    }


    // Check if there is duplicated charachter.
    for(int i = 0; i < keyLength; i++)
    {
        for(int j = i + 1; j < keyLength; j++)
        {
            if(tolower(key[i]) == tolower(key[j]))
            {
                printf("Key characters must be unique.");
                return false;
            }
        }
    }

    // Check if key length is less than 26.
    if(keyLength != 26)
    {
        printf("Key must contain 26 characters.");
        return false;
    }

    return true;
}

string encryptText(string plainText, string key)
{
    // TODO
}