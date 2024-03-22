#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int concatenate(int number1, int number2);
unsigned int hash(const char *word);
bool load(const char *dictionary);
int *int_malloc();
unsigned int *unsigned_int_malloc();
char *char_malloc();
unsigned int concatenate_ints_in_memory(int *char_values);
bool load(const char *dictionary);
node *node_malloc();

int main()
{
    char *file_path = "/Users/mherl/Documents/cs50-share/speller/speller_test/large_dict";
    load(file_path);
    return 0;
}

bool load(const char *dictionary)
{
    // TODO load into hash table
    //an array of linked lists based on the hash function

    //Step 1 
        //initiate hash table node *table[N];
        //read file
        // decide how to bucketize

    //Step 2 
        //run hash function on word
        //malloc a node node *n = malloc(sizeof(node));
        //strcopy(n->word, "some_word");
        //place node at the end of the preferred bucket
    

    //numbers starting with 0 - 9
    const int table_width = 1;
    node *hash_table[10];

    char chonk[LENGTH];
    FILE *fptr;

    fptr = fopen(dictionary, "r");

    if (fptr)
    {
        node *current_node= node_malloc();
        char *current_word = char_malloc();

        while (!feof(fptr))
        {
            fread(chonk, sizeof(chonk), 1, fptr);
            for(int i = 0; i < LENGTH + 1; i ++)
            {
                current_word[i] = chonk[i];
            }
            unsigned int hash_value = hash(current_word);
            printf("%u %s\n", hash_value, current_word);



        }
        fclose(fptr);
    }

    return false;
}

//look at node 


int concatenate(int number1, int number2)
{
    int power = 10;
    while(number2 >= power)
    {
        power *= 10;
    }
    return number1 * power + number2;
}

unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

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

int *int_malloc()
{
    const int size_char_array = sizeof(int) * (LENGTH + 1);
    int *array_to_heap = malloc(size_char_array);
    memset(array_to_heap, 0, size_char_array);
    return array_to_heap;
}

char *char_malloc()
{
    const int size_char_array = sizeof(char) * (LENGTH + 1);
    char *array_to_heap = malloc(size_char_array);
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

unsigned int concatenate_ints_in_memory(int *char_values)
{
    unsigned int concatenated_integer = 0;
    for(int i = 0; i < LENGTH; i++)
    {
        if (concatenated_integer == 0)
        {
            concatenated_integer = char_values[i];
        }
        else
        {
            concatenated_integer = concatenate(concatenated_integer, char_values[i]);
        }
    }
    return concatenated_integer;
}

node *node_malloc()
{
    const int size_node = sizeof(node);
    const int size_char_array = sizeof(char) * (LENGTH + 1);
    node *new_node = malloc(size_node);
    memset(new_node -> word, 0, size_char_array);
    return new_node;
}