// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "dictionary.h"

// TODO: Choose number of buckets in hash table
#define HASHTABLE_SIZE 10000

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Hash table
node *table[HASHTABLE_SIZE];

// Size counter
int Size_Counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Creates copy of word on which hash function can be performed
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }

    // Adds null terminator to end string
    word_copy[n] = '\0';

    // getting index of hash table for the word
    int idx = hash(word_copy);

    // Sets cursor to point to same address as hashtable
    node *w = table[idx];

    // Linked List search
    while (w != NULL)
    {
        if (strcasecmp(w->word, word_copy) == 0)
        {
            return true;
        }
        else
        {
            w = w->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // allocating space for dictionary word
    char buffer[LENGTH + 1];

    // scanning file to extract word until it reaches EOF
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // allocating apace for new node in hash table
        node *n = calloc(1, sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }

        // copying the word to a node
        strcpy(n->word, buffer);

        // using hash function to find index in hash table
        int idx = hash(n->word);
        node *head = table[idx];

        // inserting at first place
        if (head == NULL)
        {
            table[idx] = n;
            // incrementing size counter
            Size_Counter += 1;
        }
        else
        {
            // inserting new node to the hash table
            n->next = table[idx];
            table[idx] = n;
            // incrementing size counter
            Size_Counter += 1;
        }
    }

    // close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return Size_Counter;

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        // freeing linked lists
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
