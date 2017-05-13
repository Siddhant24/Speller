/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// struct for a node of trie
typedef struct trienode
{
    bool isleaf; 
    struct trienode *children[27];
}trienode;

// returns a new trie node with its children initialised to NULL

trienode *newnode(void)
{
    trienode *node = (trienode *)malloc(sizeof(trienode));
    int i;
    for(i = 0 ; i < 27 ; i++)
    {
        node->children[i] = NULL;
    }
    //node->isleaf = true;
    return node;
}

trienode *root = NULL; // root of the trie
bool isloaded;
unsigned int numwords = 0;

//inserts a string in the trie

void insert(char *word)
{
    int index,i;
    trienode *temp = root;
    int n = strlen(word);
    for(i = 0 ; i < n-1 ; i++)
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
            //if(temp->isleaf)
            //temp->isleaf = false;
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
    for(i = 0 ; i < n ; i++)
    {
        if(word[i] != '\'')
        {
            index = tolower(word[i]) - 'a';
        }
        else
        {
            index = 26;
        }
        if(temp->children[index] == NULL && temp->isleaf == false)
        return false;
        temp = temp->children[index];
        if(temp == NULL)
        return false;
    }
    if(temp->isleaf)
    return true;
    else
    return false;
}


/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    root = newnode();
    FILE* fp = fopen(dictionary, "r");
   // int index = 0;
    if(fp == NULL)
    {
        fprintf(stderr, "%s does not exist", dictionary);
        fclose(fp);
        return false;
    }
    char* word = (char *)malloc((LENGTH+1) * sizeof(char));
    while(fgets(word, LENGTH +2, fp) != NULL)
    {
       // word[strlen(word)] = '\0';
        insert(word);
        numwords++;
    }
    fclose(fp);
    isloaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(!isloaded)
    return 0;
    
    return numwords--;
}

bool removetrie(trienode *node)
{
    trienode *temp = node;
    if(temp->isleaf)
    {
        free(temp);
        return true;
    }
    int i;
    for(i = 0; i < 27 ; i++)
    {
        if(temp->children[i] != NULL)
        {
            removetrie(temp->children[i]);
        }
    }
    free(temp);
    return true;
}
/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    if(removetrie(root))
    {
       // free(root);
        return true;
    }
    return false;
}
