#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(void)
{
    //for (int i = 0; i < strlen(argv[1]); i++)
    //{
        //if (!isalpha(argv[1][i]) || argc != 2)
        //{
            //return 1;
        //}

    //}
    char* key = "BaZ";
    //printf("%s", key);
    char* plaintext = get_string("Give me a string to cipher: ");
    char* ciphertext = (char*)malloc((strlen(plaintext) + 1) * sizeof(char));
    
    int keyLength = strlen(key);

    for (int i = 0, k = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            int keychar;
            if (isupper(key[i % keyLength]))
            {
                keychar = (key[k++ % keyLength] - 'A') % 26;
            }
            else
            {
                keychar = (key[k++ % keyLength] - 'a') % 26;
            }
            //int keychar = toupper(key[k++ % keyLength] - 'A') % 26;
            //printf("%i\n", keychar);
            ciphertext[i] = ((plaintext[i] + keychar) - 'A') % 26 + 'A';
          
        }

        else if (islower(plaintext[i]))
        {
            int keychar;
            if (isupper(key[i % keyLength]))
            {
                keychar = (key[k++ % keyLength] - 'A') % 26;
            }
            else
            {
                keychar = (key[k++ % keyLength] - 'a') % 26;
            }
           
            ciphertext[i] = ((plaintext[i] + keychar) - 'a') % 26 + 'a';
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