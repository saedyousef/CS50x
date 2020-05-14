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

    // Prompt user to enter the plain text
    string plainText = get_string("plaintext: ");

    // Encrypt the plaintext
    encryptText(plainText, key);

    return 0;
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
    // Define array to collect keys characters.
    int arrayKeys[91];
    int index = 0;

    // Append the keys characters to the array.
    for(int i = 65; i <= 90; i++)
    {
        arrayKeys[i] = (int)toupper(key[index]);
        index++;
    }

    int textLength = strlen(plainText);
    char charsArray[textLength];
    char temp;

    // Replace each character in the plaintext with a character from keys array.
    for(int i = 0; i < textLength; i++)
    {
        if(isalpha(plainText[i]))
        {
            if(islower(plainText[i]))
            {
                temp = (char)tolower(arrayKeys[((int)plainText[i] - 32)]);
                charsArray[i] = temp;
            }else
            {
                temp = (char)arrayKeys[(int)plainText[i]];
                charsArray[i] = temp;
            }
        }else
        {
            charsArray[i] = plainText[i];
        }
        
    }

    // Assign the characters array into one string.
    string encryptedTex[1];
    encryptedTex[0] = charsArray;
    printf("ciphertext : %s", encryptedTex[0]);

    // Return the cipher text.
    return encryptedTex[0];
}