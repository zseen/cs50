#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const unsigned lenAlphabet = 26;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please give a key to encrypt with!\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Your key should only consist of letters!");
            return 1;
        }
    }
    char* key = argv[1];
    char* plaintext = get_string("Give me a string to cipher: ");
    char* ciphertext = (char*)malloc((strlen(plaintext) + 1) * sizeof(char));
    
    int keyLength = strlen(key);

    for (int i = 0, k = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            int keychar = (toupper(key[k++ % keyLength]) - 'A') % lenAlphabet;

            if (isupper(plaintext[i]))
            {
                ciphertext[i] = ((plaintext[i] + keychar) - 'A') % lenAlphabet + 'A';
            }
            else
            {  
                ciphertext[i] = ((plaintext[i] + keychar) - 'a') % lenAlphabet + 'a';
            }
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
