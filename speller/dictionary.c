// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int char_values[LENGTH + 1];
    for(int i = 0; i < LENGTH; i++)
    {
        int char_value = toupper(word[i]) - 0;
        char_values[i] = char_value;
    }
    char_values[LENGTH + 1] = "/0";
    int concatenated_number = 0;
    for(int i = 0; i < LENGTH; i++)
    {
        if (concatenated_number == 0)
        {
            concatenated_number = char_values[i];
        }
        else
        {
            concatenated_number = concatenate(concatenated_number, char_values[i]);
        }

    }
    return concatenated_number
}

int concatenate(int number1, int number2)
{
    int power = 10;
    while(number2 >= power)
    {
        power *= 10;
    }
    return number1 * power + number2;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
