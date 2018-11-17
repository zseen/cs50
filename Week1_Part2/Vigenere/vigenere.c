#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]) || argc != 2)
        {
            return 1;
        }

    }
    string key = (argv[1]);
    printf("%s", key);
    string plaintext = get_string("Give me a string to cipher: ");
    char ciphertext[strlen(plaintext)];
    int keyLength = strlen(key);

    for (int i = 0, k = 0; i < strlen(plaintext); i++)
    {
        //for (int j = 0; j <keyLength; j++)
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i]) - 65) + key[k++ % keyLength] % 26 + 65;
            char j = ciphertext[i];
            string g = ciphertext;
        }

        else if (islower(plaintext[i]))
        {
            ciphertext[i] = (plaintext[i]) - 97 + key[k++ % keyLength] % 26 + 97;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("%s: " "%s\n", "plaintext", plaintext);
    printf("%s: " "%s\n", "ciphertext", ciphertext);
}