#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const unsigned lenAlphabet = 26;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int key = atoi(argv[1]);
    char* plaintext = get_string("Give me a string to cipher: ");
    char* ciphertext = (char*)malloc((strlen(plaintext) + 1) * sizeof(char));

    if (ciphertext == NULL)
    {
        return 1;
    }

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] + key) - 'A') % lenAlphabet + 'A';
        }
        else if (islower(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] + key) - 'a') % lenAlphabet + 'a';
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';

    printf("%s: " "%s\n", "plaintext", plaintext);
    printf("%s: " "%s\n", "ciphertext", ciphertext);

    free(ciphertext);
}
