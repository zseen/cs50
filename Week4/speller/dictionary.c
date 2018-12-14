// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

const int MAX_HASH = 27;

// Returns true if word is in dictionary else false
bool check()//const char *word)
{
    // TODO
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
    currentNode->word = malloc(strlen(currentWord) + 1);
    strcpy(currentNode->word, currentWord);
    return currentNode;
}

void linkTwoNodes(node* firstNode, node* secondNode)
{
    firstNode->next = secondNode;
}

int getHashedValue(char* currentWord) /// maybe node.word?
{
    int sumOfChars = 0;
    for (int charPosition = 0; charPosition < strlen(currentWord); charPosition++)
    {
        sumOfChars += currentWord[charPosition];
    }

    int hashedValue = sumOfChars % MAX_HASH;
    return hashedValue;
}


void insertNodeIntoHashTable(node* currentNode, node* hashTable)
{
    int index = getHashedValue(currentNode->word);
    node* head = &hashTable[index];

    if (head == NULL)
    {
        head = currentNode;
    }
    else
    {
        currentNode->next = head;
        head = currentNode;
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
    node* hashTable = (node*)malloc(sizeof(node) * MAX_HASH);

    while (fscanf(file, "%s", currentWord) != EOF)
    {

        node* currentNode = malloc(sizeof(node));
        if (isNodeCreated(currentNode))
        {
            node* readyNode = putWordInNode(currentWord, currentNode);
            insertNodeIntoHashTable(readyNode, hashTable);
            printf("%s", readyNode->word);
        }
        else
        {
            unload();
            return false;
        }
    }

    fclose(file);

    return true;

    /*char word[LENGTH + 1] = {};
    int wordLength = strlen(word);

    create a char array node, with pointer to the next node
    make linked list strcpy(node1->word, "Hello"), then node1->next = node2
    insert node into hash table : -look up where to put it(alphabeticall ? )
    - add it to linked list nodes
    hash table : node * hashtable[]

    for every word we scan - malloc a new node, node* new_node = malloc(sizeof(node)),
        if new_node false, unload, return false, else copy word into node with strcpy(new_word->word, word)


    hash function (): */


    // TODO
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return true;
}
