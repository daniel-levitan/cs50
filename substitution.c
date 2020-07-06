#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int substitute(int letter, int *map);
bool isLower(int letter);
int checkInput(int argc, string alphabet);
bool isAlpha(string alphabet);
bool hasDuplicate(string alphabet);


const int ALPHABET_SIZE = 26;

int main(int argc, string argv[])
{
    // check if input is in the correct format
    if (checkInput(argc, argv[1]) != 0)
    {
        return 1;
    }

    // map must always be in caps - 32 is the difference between lower and upper
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (isLower(argv[1][i]))
        {
            argv[1][i] -= 32;
        }
    }

    // creating mapping
    int map[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        map[i] = argv[1][i];
    }

    string plaintext = get_string("Plaintext: ");
    int text_len = strlen(plaintext);
    int plaintext_i[text_len];
    int ciphertext[text_len];

    // replacing
    for (int i = 0; i < text_len; i++)
    {
        if ((plaintext[i] >= 'A') && (plaintext[i] <= 'Z'))
        {
            ciphertext[i] = substitute(plaintext[i], map);
        }
        else if ((plaintext[i] >= 'a') && (plaintext[i] <= 'z'))
        {
            plaintext[i] -= 32;
            ciphertext[i] = substitute(plaintext[i], map);
            ciphertext[i] += 32;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: ");
    for (int i = 0; i < text_len; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}

// substitute the letter for the map (new alphabet)
int substitute(int letter, int *map)
{
    // 65 is A in ascii
    return map[letter - 65];
}

// checks is character is lower
bool isLower(int letter)
{
    // 97 is a and 122 is z
    if ((letter >= 97) && (letter <= 122))
    {
        return true;
    }
    return false;
}

// checking for dupicate letters
// dup array is marked as 1 when a letter is found for the first time
// when the same letters is found, return true
bool hasDuplicate(string alphabet)
{
    int dup[ALPHABET_SIZE];
    char key[ALPHABET_SIZE];

    strcpy(key, alphabet);

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        dup[i] = 0;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {

        if (isLower(key[i]))
        {
            if (dup[key[i] - 97] == 0)
            {
                dup[key[i] - 97] = 1;
            }
            else
            {
                return true;
            }
        }
        else
        {
            if (dup[key[i] - 65] == 0)
            {
                dup[key[i] - 65] = 1;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

// this function test for any characters that are not letters
// letters must be in the specified range (a = 65, z = 90, A = 97, and Z = 122)
bool isAlpha(string alphabet)
{
    char key[ALPHABET_SIZE];

    strcpy(key, alphabet);

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (!(((key[i] >= 97) && (key[i] <= 122)) || ((key[i] >= 65) && (key[i] <= 90))))
        {
            return false;
        }
    }
    return true;
}

int checkInput(int argc, string alphabet)
{
    // 2 arguments are expected
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // key size check
    int key_len = strlen(alphabet);

    // checks for alphabets different from 26 letters
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // checks for non alpha characters
    if (!isAlpha(alphabet))
    {
        printf("Only letters on key\n");
        return 1;
    }

    // checks for duplicity in key
    if (hasDuplicate(alphabet))
    {
        printf("No duplicate letters\n");
        return 1;
    }

    return 0;
}