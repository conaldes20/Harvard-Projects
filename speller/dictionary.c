// Implements a dictionary's functionality

//#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

//const unsigned int LENGTH = 45;
/*
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N];
*/

#define OVERHEAD (1.1)
#define NULL_ID (-1)

struct words_list
{
    int size;
    unsigned int words[1];
};

typedef struct words_list *wordList;

wordList list_ref = NULL;

#define MIN_ID (0)
//#define MAX_ID (999999999)
#define MAX_ID (200000)

int dict_words_count = 0;

// added helper functions
wordList insertWordkey(wordList list, const char *word);
wordList createWordList(int n);
void destroyWordList(wordList list);
bool wordListContains(wordList list, const char *word);

// implementations of helper functions
// Ideas from https://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
wordList insertWordkey(wordList list, const char *word)
{
    int probe;

    unsigned int key = hash(word);
    probe = key % list->size;

    for (probe = key % list->size; list->words[probe] != NULL_ID; probe = (probe + 1) % list->size);

    list->words[probe] = key;
    dict_words_count++;

    return list;
}

wordList createWordList(int n)
{
    wordList list;
    int size;
    int i;

    size = (int)(n * OVERHEAD + 1);

    list = malloc(sizeof(*list) + sizeof(int) * (size - 1));
    if (list == 0)
    {
        return 0;
    }

    /* else */
    list->size = size;

    /* clear the hash table */
    for (i = 0; i < size; i++)
    {
        list->words[i] = NULL_ID;
    }

    return list;
}

void destroyWordList(wordList list)
{
    free(list);
    list = NULL;
}

bool wordListContains(wordList list, const char *word)
{
    int probe;

    unsigned int key = hash(word);

    /* this MUST be the same pattern as in createWordList */
    for (probe = key % list->size; list->words[probe] != NULL_ID; probe = (probe + 1) % list->size)
    {
        if (list->words[probe] == key)
        {
            return true;
        }
    }

    return false;
}

// implementations of load, hash, size, check, and unload

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO

    int chars_num = strlen(word);
    char *newWord = calloc((chars_num + 1), sizeof(char));
    //copy the newWord and make them lowercase
    for (int i = 0; i < chars_num; i++)
    {
        newWord[i] = tolower(word[i]);
    }

    bool word_found = wordListContains(list_ref, newWord);
    free(newWord);
    if (word_found)
    {
        return true;
    }

    return false;
}

unsigned int hash(const char *word)
{
    // Similar to the PJW Hash function, but tweaked for 32-bit processors.
    // It is a widley used hash function on UNIX based systems.
    unsigned int str_len = strlen(word);
    unsigned int hash = 0;
    unsigned int x    = 0;
    unsigned int i    = 0;

    for (i = 0; i < str_len; ++word, ++i)
    {
        hash = (hash << 4) + (*word);

        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }

        hash &= ~x;
    }

    return hash;
}

bool load(const char *dictionary)
{
    // Open the dictionary text file.
    FILE *the_dictionary;
    the_dictionary = fopen(dictionary, "r");

    // Check if dictionary opened correctly.
    if (the_dictionary == NULL)
    {
        printf("Failed to load dictionary");
        return false;
    }

    int n = MAX_ID;
    wordList list = createWordList(n);

    char buffer[LENGTH + 1];
    // Loop through file until end of file is reached.
    // Save each word in buffer.
    while (fscanf(the_dictionary, "%s", buffer) > 0)
    {
        int chars_num = strlen(buffer);
        char *newWord = calloc((chars_num + 1), sizeof(char));

        //copy the newWord and make them lowercase
        for (int i = 0; i < chars_num; i++)
        {
            newWord[i] = tolower(buffer[i]);
        }

        list = insertWordkey(list, newWord);
        free(newWord);
    }

    list_ref = list;

    // Done with text file.  Time to close it.
    fclose(the_dictionary);
    // Everything seems to have gone well, return true.

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO

    return dict_words_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    if (list_ref != NULL)
    {
        destroyWordList(list_ref);
        list_ref = NULL;
        return true;
    }

    return false;
}
