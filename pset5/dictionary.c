/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Global variables
#define HTSIZE 26
int dictionarySize = 0;

// Method prototype
int hashFunction(const char* key);

// Declares node and array of pointers to linked lists (hash table)
typedef struct node
{
	char stringVal[LENGTH + 1];
	struct node* nextptr;
}
node;
node* table[HTSIZE] = {NULL};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int bucket = hashFunction(word);
	node* crawler = table[bucket];

	while (crawler != NULL)
	{
		/*
		for (int i = 0; i < LENGTH+1; i++)
		{
		    tolower(word[i]);
		}
		*/
		
		if (strcasecmp(word, crawler->stringVal) == 0)
		{
			return true;
		}
		else if ((strcasecmp(word, crawler->stringVal) < 0) || (strcasecmp(word, crawler->stringVal) > 0))
		{
			crawler = crawler->nextptr;
		}
	}
	return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Opens dictionary as a stream, declares working variables
    FILE* dicptr = fopen(dictionary, "r"); 
    char word[LENGTH + 1];
    int bucket = 0;
    int wordCount = 0;

    // Error checks file pointer
    if (dicptr != NULL)
    {
        // Gets words one at a time from the stream
        while (!feof(dicptr))
        {
            if (fscanf(dicptr, "%s", word) > 0)
            {
                wordCount ++;    
            }

            // Sets hash table index
            bucket = hashFunction(word);

            // Creates first node if non-extant
            if (table[bucket] == NULL)
            {
                node* first = malloc(sizeof(node));
                table[bucket] = first;
                strcpy(first->stringVal, word);
                first->nextptr = NULL;
            }

            // Traverses the list, creates node at the tail
            else
            {
                node* crawler = table[bucket];

                while (crawler->nextptr != NULL)
                {
                    crawler = crawler->nextptr;
                }
                
                node* new = malloc(sizeof(node));
                crawler->nextptr = new;
                strcpy(new->stringVal, word);
                new->nextptr = NULL;
            }
        }
        dictionarySize = wordCount;
        fclose(dicptr);
        return true;
    }
    return false;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (dictionarySize > 0)
    {
        return dictionarySize;
    }
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HTSIZE; i++)
	{
		node* traverser = table[i];
		
		while (traverser != NULL)
		{
			node* temp = traverser;
			traverser = traverser->nextptr;
			free(temp);
		}
	}
	return true;
}

//hash method
int hashFunction(const char* key)
{
    int hash = (toupper(key[0]) - 'A');
    return hash % HTSIZE;
}
