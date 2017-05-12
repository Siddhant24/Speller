/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

// struct for a node of trie
typedef struct trienode
{
    bool isleaf; 
    struct trienode *children[27];
}trienode;

trienode *root; // root of the trie
root = (trienode *)malloc(sizeof(trienode));
// returns a new trie node with its children initialised to NULL

trienode *newnode(void)
{
    trienode *node = (trienode *)malloc(sizeof(trienode));
    int i;
    for(i = 0 ; i < 27 ; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

//inserts a string in the trie

void insert(char *word)
{
    int index,i;
    trienode *temp = root;
    int n = strlen(word);
    for(i = 0 ; i < n ; i++)
    {
        if(word[i] != '\'')
        {
            index = word[i] - 'a';
        }
        else
        {
            index = 26;
        }
        if(temp->children[index] == NULL)
        {
            temp->children[index] = newnode();
        }
        temp = temp->children[index];
    }
    temp->isleaf = true;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    trienode *temp = root;
    int index, i, n;
    n = strlen(word);
    for(i = 0 ; i < 27 ; i++)
    {
        if(word[i] != '\'')
        {
            index = word[i] - 'a';
        }
        else
        {
            index = 26;
        }
        if(temp->children[index] == NULL && temp->isleaf == false)
        return false;
    }
    return true;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* inptr = fopen(dictionary, "r");
    if(inptr == NULL)
    {
        fprintf(stderr, "%s does not exist", dictionary);
        fclose(inptr);
        return false;
    }
    char* word = (char *)malloc((LENGTH+1) * sizeof(char));
    while(fgets(word, LENGTH, inptr) != EOF)
    {
        insert(word);
    }
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
