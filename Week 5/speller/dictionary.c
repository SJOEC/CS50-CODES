// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// word counter to implement the funtion size
int word_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // set cursor to an element in the array opf nodes
    node *cursor = table[hash(word)];

    // while cursor isn´t NULL
    while (cursor != NULL)
    {
        // check if the actual cursor-word is equals to the word, return true
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        // if isn't equal, move into the next word
        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // initializa tyhe hash value
    int hash_letter = 0;

    // for each letter
    for (int i = 0; i < strlen(word); i++)
    {
        // add the value of itself
        hash_letter += toupper(word[i]);
    }

    hash_letter = hash_letter % N;

    return hash_letter;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // initialize a buffer to store the word
    char buffer[LENGTH + 1];

    // open dictionary file
    FILE *dictionary_file = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Could not open the file.\n");
        return false;
    }

    // Read strings from the file one at a time
    while (fscanf(dictionary_file, "%s", buffer) != EOF)
    {
        // allocate a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Program is runnig out of memory\n");
            return false;
        }

        // copy the word into the node
        strcpy(n->word, buffer);

        // point the new node to the first word in the hash table
        n -> next = table[hash(buffer)];

        // point the hash table to the new node
        table[hash(buffer)] = n;

        word_counter ++;

    }
    fclose(dictionary_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // for each location in the array
    for (int i = 0; i < N; i++)
    {
        // cursor in the first node at position i
        node *cursor_free = table[i];

        while (cursor_free != NULL)
        {
            // temp at the same position as cursor
            node *tmp = cursor_free;

            // move into the next node
            cursor_free = cursor_free -> next;

            // free the previous node
            free(tmp);
        }

        if (i == N - 1)
        {
            return true;
        }

    }
    return false;
}
