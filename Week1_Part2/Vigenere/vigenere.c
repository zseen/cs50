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
    //printf("%s", key);
    string plaintext = get_string("Give me a string to cipher: ");
    char ciphertext[strlen(plaintext)];
    int keyLength = strlen(key);

    for (int i = 0, k = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            int keychar = tolower(key[k++ % keyLength] - 97) % 26;
            //printf("%i\n", keychar);
            ciphertext[i] = ((plaintext[i] + keychar) - 'A') % 26 + 'A';
            char q = ciphertext[i];
            string g = ciphertext;
        }

        else if (islower(plaintext[i]))
        {
            int keychar = tolower(key[k++ % keyLength] - 97) % 26;
            ciphertext[i] = ((plaintext[i] + keychar) - 'a') % 26 + 'a';
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("%s: " "%s\n", "plaintext", plaintext);
    printf("%s: " "%s\n", "ciphertext", ciphertext);
}