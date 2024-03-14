// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
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
    //Convert word string to a set of character ints
    //Place each char int in the char values array
    int *char_values = int_malloc();
    int str_length = 0;
    for(int i = 0; i < LENGTH + 1; i ++)
    {
        if(word[i])
        {
            char_values[i] = toupper(word[i]);
        }
        else
        {
            str_length = i;
            break;
        }

    }
    //I used http://www.cs.cmu.edu/afs/cs/academic/class/15210-s15/www/lectures/hash-notes.pdf
    //as inspiration for this hash because it was a little more 
    //friendly than http://math.uchicago.edu/~may/REU2020/REUPapers/Miller.pdf

    //I went down a rabbit hole looking at cool polynomials, but I have a hard time reading formal
    //notation so lets just call this my "interpretation" of wilkinson's polynomial evaluated at 
    //char_int

    //Step 1: Evaluate a wilkinson's polynomial term at different char_int. 
    //        Multiply it by the product of previous wilkinsons terms
    //Step 3: Add the values to receive a unique value

    int count = 1;
    unsigned int wilkinsons_value = 1;
    unsigned int *hash_values = unsigned_int_malloc();
    for(int i = 1; i < str_length + 1; i ++)
    {
        wilkinsons_value = wilkinsons_value * (char_values[i - 1] - i);
        hash_values[i - 1] = wilkinsons_value;
        wilkinsons_value = (wilkinsons_value % 512) + 1;
    }
    free(char_values);

    unsigned long int hash_sum = 0;

    for(int i = 0; i < str_length + 1; i ++)
    {
        hash_sum = hash_sum + hash_values[i];
    }
    hash_sum = hash_sum % UINT_MAX;

    free(hash_values);

    return hash_sum;
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
int *int_malloc()
{
    const int size_char_array = sizeof(int) * (LENGTH + 1);
    int *array_to_heap = malloc(size_char_array);
    memset(array_to_heap, 0, size_char_array);
    return array_to_heap;
}

unsigned int *unsigned_int_malloc()
{
    const int size_char_array = sizeof(unsigned int) * (LENGTH + 1);
    unsigned int *array_to_heap = malloc(size_char_array);
    memset(array_to_heap, 0, size_char_array);
    return array_to_heap;
}