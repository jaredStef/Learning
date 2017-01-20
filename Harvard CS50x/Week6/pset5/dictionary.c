/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality
 * using a trie data type
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

typedef struct trie_node
{
    char c;
    bool indexIsEndOfWord;
    struct trie_node* next;
} trie_node;

trie_node* root;

int words = 0;

bool letterInTrie(char c, trie_node* trie);
int indexForChar(char c);
bool deallocTrie(trie_node* node);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    trie_node* current = root;

    // lowercase a copy of the word
    char* cWord = malloc(sizeof(char) * strlen(word));

    for (int i = 0; i < strlen(word); i++)
    {
        cWord[i] = tolower(word[i]);
    }

    // for each char
    for (int i = 0; i < strlen(cWord); i++)
    {
        char c = cWord[i];

        // check if i == strlen - 1 and if so return if c is in trie and if it is the end of a word
        if (i == strlen(word) - 1)
        {
            return current[indexForChar(c)].indexIsEndOfWord;
        }
        else
        {
            // check if char is in current
            if (letterInTrie(c, current))
            {
                 // if it is and next is null return false
                 if (current[indexForChar(c)].next == NULL)
                 {
                     return false;
                 }
                 else
                 {
                     // if so set current to the next trie and call again
                     current = current[indexForChar(c)].next;
                 }
            }
            else
            {
                // if not return false
                return false;
            }
        }
    }
    return false;
}

bool letterInTrie(char c, trie_node* trie)
{
    return trie[indexForChar(c)].c == c;
}

void printTrie(trie_node* node)
{
    if (node == NULL) { return; } else { printf("\n"); } ;
    while (true)
    {
        trie_node* current = node;
        for (int i = 0; i < 27; i++)
        {
            if (current[i].c == 0x0)
            {
                printf("[N]");
            }
            else
            {
                printf("[%c,%i]", current[i].c, current[i].indexIsEndOfWord);
                // recursion
                printTrie(current[i].next);
            }
        }
        break;
    }
    printf("\n");
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    root = malloc(sizeof(trie_node) * 27);
    trie_node* current = root;

    FILE* dict = fopen(dictionary, "r");
    const int lineSize = 128;
    char line[lineSize];

    while(fgets(line,lineSize,dict))
    {
        char c;
        // run for each char
        for ( int i = 0; i < lineSize; i++ )
        {
            if (line[i] == EOF)
            {
                continue;
            }

            if (!line[i] || line[i] == 10) { break; }
            c = tolower(line[i]);

            if (i > 0 && current[indexForChar(line[i - 1])].next == NULL)
            {
                trie_node* nTrie = malloc(sizeof(trie_node) * 27);
                current[indexForChar(line[i - 1])].next = nTrie;
                current = nTrie;
            }
            else if (i > 0)
            {
                current = current[indexForChar(line[i - 1])].next;
            }
            current[indexForChar(c)].c = c;
        }

        // Run at end of word
        words += 1;
        current[indexForChar(c)].indexIsEndOfWord = true;
        current = root;
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return deallocTrie(root);
}

/**
 * Recursively goes to the deepest node (the one in which all nodes.next is NULL)
 * and frees them until returning to root
 */
bool deallocTrie(trie_node* node)
{
    for (int i = 0; i < 27; i++)
    {
        if (node[i].next != NULL)
        {
            // recursion
            deallocTrie(node[i].next);
        }
    }
    free(node);
    return true;
}

int indexForChar(char c)
{
    return c == '\'' ? 26 : tolower(c) - 'a';
}
