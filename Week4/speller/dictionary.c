// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

const int MAX_HASH = 27;
node** hashTable = NULL;
int wordsInDictCounter;

void makeHashTable()
{
    hashTable = (node**)malloc(sizeof(node) * MAX_HASH);
}

int getHashedValue(const char* currentWord) /// maybe node.word?
{
    int sumOfChars = 0;
    for (int charPosition = 0; charPosition < strlen(currentWord); charPosition++)
    {
        sumOfChars += currentWord[charPosition];
    }

    int hashedValue = sumOfChars % MAX_HASH;
    return hashedValue;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    char* lowerCaseWord = (char*)malloc(sizeof(char) * strlen(word));
    for (int i = 0; i < strlen(word); ++i)
    {
        lowerCaseWord[i] = tolower(word[i]);
    }

    lowerCaseWord[strlen(word)] = '\0';
    int index = getHashedValue(lowerCaseWord);
    node* locationHead = hashTable[index];
    node* cursor = locationHead;

    while (cursor != NULL)
    {
        if (strcmp(cursor->word, lowerCaseWord) == 0)
        {
            free(lowerCaseWord);
            return true;
        }
        else
        {
            cursor = cursor->next;
        }    
    }

    free(lowerCaseWord);
    return false;
}


bool isNodeCreated(node* currentNode)
{
    if (currentNode == NULL)
    {
        return false;
    }
    return true;
}

node* putWordInNode(char* currentWord, node* currentNode)
{
    currentNode->word = malloc((strlen(currentWord)) + 1);
    strcpy(currentNode->word, currentWord);
    return currentNode;
}


void insertNodeIntoHashTable(node* currentNode)
{
    int index = getHashedValue(currentNode->word);


    if (hashTable[index] == NULL)
    {
        hashTable[index] = currentNode;
    }
    else
    {
        currentNode->next = hashTable[index];
        hashTable[index] = currentNode;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Could not open dictionary");
        return false;
    }

    char currentWord[LENGTH + 1];
    //node* hashTable = (node*)malloc(sizeof(node) * MAX_HASH);

    makeHashTable();

    while (fscanf(file, "%s", currentWord) != EOF)
    {
        node* currentNode = malloc(sizeof(node));
        if (isNodeCreated(currentNode))
        {
            node* readyNode = putWordInNode(currentWord, currentNode);
            insertNodeIntoHashTable(readyNode);
            //printf("%s", readyNode->word);
            wordsInDictCounter++;
        }
        else
        {
            unload();
            return false;
        }
    }

    fclose(file);

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordsInDictCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < MAX_HASH; ++i)
    {
        node* cursor = hashTable[i];

        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp->word);
            free(temp);
        }
    }

    free(hashTable);
    return true;
}
