#include <stdio.h>
#include <cs50.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE


char* generateInitialPW(int size)
{
    char* initialPW = (char*)malloc((size + 1) * sizeof(char));

    for (int i = 0; i < size; i++)
    {
        initialPW[i] = 'A';
    }
    initialPW[size] = '\0';
    return initialPW;
}

char* generateFinalPW(int size)
{
    char* finalPW = (char*)malloc((size + 1) * sizeof(char));

    for (int i = 0; i < size; i++)
    {
        finalPW[i] = 'z';
    }

    finalPW[size] = '\0';
    return finalPW;
}

void getLexicographicalNextString(char* c)
{
    for (int i = strlen(c) - 1; i >= 0; i -= 1)
    {
        if (c[i] == 'Z')
        {
            c[i] = 'a';
            break;
        }
        else if (c[i] == 'z')
        {
            c[i] = 'A';

        }
        else
        {
            c[i] += 1;
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Please give me a hash!\n");
        return 1;
    }

    char* targetHash = argv[1];
    char password[6] = { '\0' };
    char salt[3] = { targetHash[0], targetHash[1], '\0' };

    for (int passwordLength = 1; passwordLength < 6; passwordLength++)
    {
        char* currentPW = generateInitialPW(passwordLength);
        char* finalPW = generateFinalPW(passwordLength);

        while (true)
        {         
            if (strcmp(currentPW, finalPW) == 0)
            {
                break;
            }

            char* hash = crypt(currentPW, salt);
            if (strcmp(hash, targetHash) == 0)
            {
                printf("%s\n", currentPW);
                return 0;
            }                   
                getLexicographicalNextString(currentPW);            
        }
        free(currentPW);
        free(finalPW);
    }
    return 1;
}