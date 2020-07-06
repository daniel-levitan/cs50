#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Checking if only 1 argument is provided, if not, reject
    if (argc != 2)
    {
        printf("Usage ./caesar key");
        return 1;
    }

    // check if only numbers were provided in the argument, if not reject
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Usage ./caesar key");
            return 1;
        }
    }

    // converting char to int
    int key = atoi(argv[1]);

    string plaintext = get_string("Plaintext: ");

    // run algorithm
    int n = strlen(plaintext);
    int ciphertext[n];

    for (int i = 0; i < n; i++)
    {
        // if char between a and z, convert, bring a to 0 by decreasing 97 from it, and summing after the conversion
        // if char between A and Z, convert, bring A to 0 by decreasing 97 from it, and summing after the conversion
        // else, only copy the char
        if ((plaintext[i] >= 'a' && plaintext[i] <= 'z'))
        {
            ciphertext[i] = ((plaintext[i] + key - 97) % 26) + 97;
        }
        else if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
        {

            ciphertext[i] = ((plaintext[i] + key - 65) % 26) + 65;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    printf("ciphertext: ");
    // printing each character as char, since we have it as int
    for (int i = 0; i < n; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}

