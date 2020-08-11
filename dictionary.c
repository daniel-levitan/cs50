// Implements a dictionary's functionality

#include <stdbool.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Point to dictionary
FILE *dict_file_handler = NULL;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
// const unsigned int N = 1;
const unsigned int N = 100000;

// Hash table
node *table[N];


bool include_word(char *word)
{
    // the index of the hash table(vector) is the lower cased first letter ascii code minus 97 (ascii offset)
    // int index = tolower(word[0]) - 97;
    int index = hash(word);


    // fill up new node info
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        return false;
    }
    strcpy(new_node->word, word);
    new_node->next = NULL;

    node *list = table[index];
    if (list == NULL)
    {
        table[index] = new_node;
    }
    else
    {
        node *tmp = list;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new_node;
    }
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char new_word[LENGTH + 1];

    int i = 0;
    while (word[i] != '\0')
    {
        new_word[i] = tolower(word[i]);
        i++;
    }
    new_word[i] = '\0';

    int index = hash(new_word);

    if (table[index] == NULL)
    {
        return false;
    }

    node *tmp = table[index];
    while (tmp != NULL)
    {
        if (strcmp(tmp->word, new_word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // return tolower(word[0]) - 97;

    unsigned long hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // resetting the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    dict_file_handler = fopen(dictionary, "r");
    if (dict_file_handler == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    // word index
    int i = 0;
    char word[LENGTH + 1];

    for (int c = fgetc(dict_file_handler); c != EOF; c = fgetc(dict_file_handler))
    {
        if (c != '\n')
        {
            word[i] = c;
            i++;
        }
        else
        {
            word[i] = '\0';
            i = 0;
            if (!include_word(word))
            {
                fclose(dict_file_handler);
                return false;
            }
        }
    }

    fclose(dict_file_handler);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int sum = 0;

    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *tmp = table[i];
            while (tmp->next != NULL)
            {
                sum++;
                tmp = tmp->next;
            }
            sum++;
        }
    }

    return sum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *list = table[i];
            node *tmp = NULL;

            while (list != NULL)
            {
                tmp = list->next;
                free(list);
                list = tmp;
            }
        }
    }
    return true;
}
