// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stddef.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 18278;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // problem with the input to the function
    if (word == NULL)
    {
        printf("bad input\n");
        return false;
    }
    // Generate hash
    int key = hash(word);
    if (key == 0)
    {
        return false;
    }

    // Loop over the hash table looking for a match
    if (table[key] == NULL)  // no words linked to this key
    {
        return false;
    }
    else
    {
        node *tmp = table[key];
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
            if (strcasecmp(tmp->word, word) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int key = 0;

    // travel first 3 chars, mapping ascii letters to 1-26, calculate the key
    for (int c = 0; word[c] != '\0' && c < 3; c++)
    {
        char smallLetter = tolower(word[c]);
        int mappedLetter = (int)(smallLetter) - 96;  // a = 1, b = 2, c = 3...
        if (mappedLetter > 0 && mappedLetter < 27)
        {
            key += mappedLetter * pow(26, c);
        }
        else
        {
            continue;
        }
    }
    return key;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open the dictionary
    FILE *pDictionary = fopen(dictionary, "r");
    if (pDictionary == NULL)
    {
        return false;
    }

    // holding 1 word at a time
    char word[LENGTH + 1];
    // representing the place in the word
    int index = 0;

    // Spell-check each word in dictionary
    for (int c = fgetc(pDictionary); c != EOF; c = fgetc(pDictionary))
    {
        // Allow only alphabetical characters and apostrophes in middle of words
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(pDictionary)) != EOF && isalpha(c));

                // Prepare for new word
                index = 0;
            }
        }

        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(pDictionary)) != EOF && isalnum(c));

            // Prepare for new word
            index = 0;
        }

        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            word[index] = '\0';

            // Create a node
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }
            strcpy(n->word, word);
            n->next = NULL;

            // Generate hash
            int key = hash(word);
            if (key == 0)
            {
                return false;
            }

            // Feed the rigth hash table slot at the end
            if (table[key] == NULL)  // no key yet
            {
                table[key] = n;
            }
            else
            {
                node *tmp = table[key];
                while (tmp->next != NULL)
                {
                    tmp = tmp->next;
                }
                tmp->next = n;
            }

            // Prepare for next word
            index = 0;
        }
    }
    // Check whether there was an error
    if (ferror(pDictionary))
    {
        fclose(pDictionary);
        printf("Error reading %s.\n", dictionary);
        unload();
        return 1;
    }

    // close dictionary
    fclose(pDictionary);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            tmp = tmp->next;
            counter++;
        }
    }
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
