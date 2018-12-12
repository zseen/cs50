// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

node* createNode(char* currentWord)
{   
    node* currentNode = malloc(sizeof(node));
    strcpy(currentNode -> word, currentWord);
    return currentNode;
}

void linkTwoNodes(node* firstNode, node* secondNode)
{
    firstNode -> next = secondNode;
}



node* createHashTable()
{
    node* hashTable[27];
}


void insertNodeIntoHashTable(node currentNode, node* hashTable)
{
    if (hashTable[]



        if hashtable[hash] is NULL
            make hashtable[hash] point to new_node
        else
            create a temporary_node
            make temporary_node point to where hashtable[hash] is pointing
            while temporary_node not NULL
                make temporary_node point to where temporary_node->next is pointing
                make temporary_node->next point to new_node
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* file;
    file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open dictionary");
        return false;
    }





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
    return false;
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
    return false;
}
