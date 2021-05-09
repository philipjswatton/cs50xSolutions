// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// The following resources used in the process of creating the below code
// - https://stackoverflow.com/questions/31930046/what-is-a-hash-table-and-how-do-you-make-it-in-c     for general understanding
// - http://www.cse.yorku.ca/~oz/hash.html                                                             for the hash function used in this code
// - https://www.dcode.fr/closest-prime-number                                                         for choosing N


// for initial testing: ./speller dictionaries/small texts/cat.txt


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 174721; //try 65536, 143093, 174721


// Hash table <- this is a global variable/table that functions will refer to
node *table[N]  = {NULL}; //initialising the table's elements as NULL



// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    int len = strlen(word);
    char lword[LENGTH + 1] = {'\0'};

    // Convert word to low'er case for comparison
    for (int i = 0; i < len; i++) {
        lword[i] = tolower(word[i]);
    }

    // Get hash code for word
    int val = hash(lword);

    // Check
    node *tmp = table[val];

    while(tmp != NULL) {
        if (strcmp(tmp->word, lword) == 0) {
            return true;
        } else {
            tmp = tmp->next;
        }
    }

    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    // Using djb2 - can add modulo N to constrain to fit within a certain number of boxes - so long as N is a prime number

    unsigned int hash = 5381;
    int c;
    int len = strlen(word);

    for(int i = 0; i < len; i++) {
        c = word[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    hash = hash % N;

    return hash;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");

    // for each word in the dictionary:
    // - iterate over file to get words
    // - put word in hash function
    // - create node, put word in
    // - put node in bin, repeat
    // at the end, close the file
    // return true if successful

    char word[LENGTH + 1] = {'\0'};
    int val = 0;

    while(fscanf(dic, "%s", word) != EOF) {

        // get hash location
        val = hash(word);

        // create node
        node *n = malloc(sizeof(node));
        if (n == NULL) {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        if (table[val] == NULL) {
            // if location is NULL, make the node the location
            table[val] = n;
        } else {
            // else if location is not NULL, prepend the new node
            node*tmp = table[val];
            n->next = tmp;
            table[val] = n;
        }
    }

    fclose(dic);

    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    //Initialise count
    int count = 0;

    // Count the words
    for (int i = 0; i < N; i++) {

        if (table[i] != NULL) {

            node *tmp = table[i];
            while(true) {
                count++;
                tmp = tmp->next;

                if (tmp == NULL) {
                    break;
                }
            }

        }
    }

    // Return count
    return count;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i < N; i++) {

        if (table[i] != NULL) {

            while(table[i] != NULL) {
                node *tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
        }

        if (table[i] != NULL) {
            return false;
        }
    }

    return true;
}
