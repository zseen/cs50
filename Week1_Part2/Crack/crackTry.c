#include <stdio.h>
#include <cs50.h>
#include <io.h>
//#include <crypt.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE


char* generateInitialPW(int size)
{
    char* guess = (char*)malloc((size + 1) * sizeof(char));
    //alloc char* array guess i length, beletölt size db a-t
    for (int i = 0; i < size; i++)
    {
        guess[i] = 'A';
    }
        
   
    guess[size] = '\0';
    //how does it generate the in.pw?
    //printf("%s", guess);
    return guess;
}

char* generateFinalPW(int size)
{
    //from the end, fill up with 'Z'-s
    char* finPW = (char*)malloc((size + 1) * sizeof(char));
    
    //what does it exactly do? ad how?
    for (int i = 0; i < size; i++)
    {
        finPW[i] = 'z';
    }
    finPW[size] = '\0';
    return finPW;
}



void getLexicographicalNextString(char* c) // c is a pointer to a char array
{
    //how does it get the next lexicographical string? 
    //a - b- c -....z    A -- Z abZ aca 
    //char* alphabet = (char*)malloc((53 * sizeof(char)));

   //const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //abcdefghijklmnopqrstuvwxyz
    //ABCDEFGHIJKLMNOPQRSTUVWXYZ 
    for (int i = strlen(c) - 1; i >= 0; i -= 1)
       
    {
        if (c[i] == 'Z')
        {
            c[i] = 'a';
            //c[i - 1] += 1;
            break;
        }
        else if (c[i] == 'z')
        { 
            c[i] = 'A';

            int step = 1;
            
            while (c[i - step] == 'Z')
            {
                c[i - step] = 'a';
                step++; 
            }

            while (c[i - step] == 'z')
            {
                c[i - step] = "A";
                step++;
            }
            
            c[i - 1] += 1;
            break;
                                       
        }
        else
        {
            c[i] += 1;
            break;
        } 
    }  
    
    //printf("%s", c);
}


int main(int argc, char* argv[])
{
    //*if (argc != 2)
    /*{
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
    }*/
    char* targetHash = argv[1];
    char password[6] = { '\0' };
    char salt[3] = {targetHash[0], targetHash[1], '\0'};

    for (int passwordLength = 1; passwordLength < 6; passwordLength++)
    {
        char* currentPW = generateInitialPW(passwordLength);
        char* finalPW = generateFinalPW(passwordLength);

        while (strcmp(currentPW, finalPW) != 0) // not equals
        {
            //char* hash = crypt(currentPW, salt); // from the crypt library
            /*if (strcmp(hash, targetHash) == 0)
            {
                printf("Solution, %s", currentPW);
                return 0;
            }*/
            printf("%s: %s\n", "currentPW", currentPW);
            //printf("%s: %s\n", "finalPW", finalPW);
            getLexicographicalNextString(currentPW);
            
            
        }
    }

    return 1;
}