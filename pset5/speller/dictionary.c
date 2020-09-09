// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 40000;

// Hash table
node *table[N];

unsigned int word_count = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int h = hash(word);

    for( node *temp = table[h]; temp!= NULL; temp = temp->next)
    {
        if (strcasecmp(word, temp->word) ==0 )
        {
            return true;
        }
    }
    return false;
}


// Hashes word to a number
// Djb2 hash function
// Source => http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char words[LENGTH+1];

    FILE *f= fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }

    while(fscanf(f, "%s", words) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, words);
        n->next = NULL;

        int h = hash(n->word);

        if (table[h] == NULL)
        {
            table[h] = n;
            word_count++;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
            word_count++;
        }
    }
    fclose(f);
return true;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // if (!load(&dictionary))
    // {
    //       return 0;
    // }

    // else
    // {
        return word_count++;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    for (unsigned int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;

}
