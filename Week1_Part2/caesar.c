#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
    return 1;
    }

    int key = atoi(argv[1]);
    string plaintext = get_string("Give me a string to cipher: ");
    char ciphertext[strlen(plaintext)];

    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] + key) - 65) % 26 + 65;
        }

        else if (islower(plaintext[i]))
        {
            ciphertext[i] = ((plaintext[i] + key) - 97) % 26 + 97;
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("%s: " "%s\n", "plaintext", plaintext);
    printf("%s: " "%s\n", "ciphertext", ciphertext);
}
