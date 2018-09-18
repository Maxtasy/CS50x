// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// create array of pointer-to-nodes of size HASHTABLE_SIZE
node *hashtable[HASHTABLE_SIZE];

// Global variable to store number of words in our dictionary
unsigned int word_count = 0;

// Global boolean for tracking load/unload dictionary operations
bool loaded = false;

// Hash function returns bucket number
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(needs_hashing); i < n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Create char array to store copy of word
    // Word is a const char* and non-read actions cannot be performed on it
    int len = strlen(word);
    char word_copy[len + 1];

    // Convert word to lowercase and store it in word_copy
    for (int i = 0; i < len; i++)
    {
       word_copy[i] = tolower(word[i]);
    }

    // Add null terminator to end of char array
    word_copy[len] = '\0';

    // Get hash value (a.k.a. bucket)
    int h = hash_it(word_copy);

    // Assign cursor node to the first node of the bucket
    node *cursor = hashtable[h];

    // Check until the end of the linked list
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, word_copy) == 0)
        {
            // Word is in dictionary
            return true;
        }
        else
        {
            // Check next node
            cursor = cursor->next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE* dict = fopen(dictionary, "r");
    if (!dict)
    {
        printf("Could not open dictionary.\n");
        return false;
    }

    while (true)
    {
        // Malloc a node for each new word
        node *new_node = malloc(sizeof(node));
        if (!new_node)
        {
            printf("Could not malloc a new node.\n");
            return false;
        }

        // Read a word from the dictionary and store it in new_node->word
        fscanf(dict, "%s", new_node->word);
        new_node->next = NULL;

        if (feof(dict))
        {
            // hit end of file
            free(new_node);
            break;
        }

        word_count++;

        // hashtable[h] is a pointer to a key-value pair
        int h = hash_it(new_node->word);
        node *head = hashtable[h];

        // if bucket is empty, insert the first node
        if (head == NULL)
        {
            hashtable[h] = new_node;
        }
        // if bucket is not empty, attach node to front of list
        // design choice: unsorted linked list to minimize load time rather
        // than sorted linked list to minimize check time
        else
        {
            new_node->next = hashtable[h];
            hashtable[h] = new_node;
        }
    }

    // close dictionary
    fclose(dict);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];
        while (cursor != NULL)
        {
            // Maintain connection to linked list using temp
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    loaded = false;
    return true;
}
