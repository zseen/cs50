
#include <stdio.h>
#include <cs50.h>
#include <io.h>
//#include <crypt.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE



char* createAlphabet(firstLetter)
{
    char alphabet[26];

    for (int letter = firstLetter, i = 0; letter < ((int)firstLetter + 26); letter++)
    {
        alphabet[i++] = (char)letter;
        //printf("%c", letter);
       
    }
    char* alp = (char*)malloc((strlen(alphabet) + 1) * sizeof(char));
    return alp;
}




int main(void)
{
    /*if (argc != 2)
    {
        printf("Please give a key to encrypt with!\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Your key should only consist of letters!\n");
            return 1;
        }
    }
*/
    //char alphabet[53];
    //char* hashedPassword = argv[1];
    //char password[6] = { '\0' };
    //char* salt[3] = {hashedPassword[0], hashedPassword[1]};

    char* alphabet[26] = {0};
    createAlphabet('A', alphabet);
    
    for (int i = 0; i < 26; i++)
    {
        printf("%c", alphabet[i]);
    } 
}