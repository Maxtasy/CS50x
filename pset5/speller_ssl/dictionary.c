// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Define node structure
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Declare global head and set pointer to NULL
node *head;

// Declare global wvariable ord_count which we increase within load()
unsigned int word_count = 0;

// Declare global variable loaded to keep track if our dictionary is loaded or not
bool loaded = false;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Make copy of word and transform it to lowercase
    char *word_copy = malloc(sizeof(word));

    for (int i = 0; i < strlen(word); i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    word_copy[strlen(word)] = '\0';

    // Set trav to head
    node *trav = head;

    // Check each node until we reach the NULL pointer at the end of the linked list
    while (trav != NULL)
    {
        if (strcmp(word_copy, trav->word) == 0)
        {
            // Word found in dictionary
            free(word_copy);
            return true;
        }
        else
        {
            // Go to next node
            trav = trav->next;
        }
    }
    free(word_copy);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        printf("Couldn't open dictionary.\n");
        return false;
    }

    // Initialze head node for linked list
    head = malloc(sizeof(node));
    if (!head)
    {
        printf("Couldn't create head node.\n");
        return false;
    }

    // Add words to dictionary
    while (true)
    {
        // Create new node
        node *new_node = malloc(sizeof(node));

        // Check if memory got allocated
        if (!new_node)
        {
            printf("Couldn't create new node.\n");
            return false;
        }

        fscanf(dict, "%s", new_node->word);

        // Break if we are at the end of the dictionary
        if (feof(dict))
        {
            free(new_node);
            break;
        }

        new_node->next = head->next;
        head->next = new_node;

        // Increment global variable word_count
        word_count++;
    }

    // Close dictionary and set global variable loaded to true
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
    // Create cursor pointing at head
    node *cursor = head;
    while (cursor)
    {
        // Create temporary copy of corsor so we can free current node
        node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }

    // Set global variable loaded to false
    loaded = false;
    return true;
}
