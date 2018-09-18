// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Create global variable to store number of words in dictionary
unsigned int word_count = 0;

// Create global variable to keep track of load status
bool loaded = false;

// Create node struct
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Create array of nodes with HASHTABLE_SIZE elements CHECK IF * NEEDED
node *hashtable[HASHTABLE_SIZE];

// Hash function credit to *********INSERT**********
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
    // Make a copy of word we can work with, set all letters to lower case
    char word_copy[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    word_copy[strlen(word)] = '\0';

    // Get hash value of word
    int hash_value = hash_it(word_copy);

    node *trav = hashtable[hash_value];

    while (trav != NULL)
    {
        if (strcmp(trav->word, word_copy) == 0)
        {
            return true;
        }

        trav = trav->next;
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Set pointers of all elements to NULL
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        printf("Couldn't open dictionary file.\n");
        return false;
    }

    // Add words to dictionary in memory
    while (true)
    {
        // Create new node
        node *new_node = malloc(sizeof(node));

        if (!new_node)
        {
            printf("Couldn't create new node.\n");
            return false;
        }

        fscanf(dict, "%s", new_node->word);
        new_node->next = NULL;

        // Free memory and return true if we reached the end of the file
        if (feof(dict))
        {
            free(new_node);
            break;
        }

        word_count++;

        // Get hash value of word
        int hash_value = hash_it(new_node->word);

        // Set new_node's next pointer to the next element in the bucket
        new_node->next = hashtable[hash_value];

        // Set bucket's pointer to new_node
        hashtable[hash_value] = new_node;
    }

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
    // Iterate over all buckets of the hashtable
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *trav = hashtable[i];

        while(trav != NULL)
        {
            node *temp = trav;
            trav = trav->next;
            free(temp);
        }
    }

    loaded = false;
    return true;
}
