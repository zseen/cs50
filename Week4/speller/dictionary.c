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
    int index = getHashedValue(word);
    node* locationHead = hashTable[index];
    node* cursor = locationHead;

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }    
    }

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
    // TODO
    return true;
}
