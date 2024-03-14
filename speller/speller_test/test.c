#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 45
int concatenate(int number1, int number2);
unsigned int hash(const char *word);

//This returns a malloc pointer and does not free
int *int_malloc();
unsigned int *unsigned_int_malloc();
unsigned int concatenate_ints_in_memory(int *char_values);


int main()
{
    const char *word = "This is some real bullshit right here ";
    unsigned int hash_value = hash(word);
    return 0;
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

unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    //Convert word string to a set of character ints
    //Place each char int in the char values array
    int *char_values = int_malloc();
    for(int i = 0; i < LENGTH + 1; i ++)
    {
        if(word[i])
        {
            char_values[i] = toupper(word[i]);
        }
        else
        {
            break;
        }

    }

    //I used http://www.cs.cmu.edu/afs/cs/academic/class/15210-s15/www/lectures/hash-notes.pdf
    //as inspiration for this hash because it was a little more 
    //friendly than http://math.uchicago.edu/~may/REU2020/REUPapers/Miller.pdf

    //I went down a rabbit hole looking at cool polynomials, but I have a hard time reading formal
    //notation so lets just call this my "interpretation" of wilkinson's polynomial evaluated at 
    //char_int

    //Step 1: Evaluate a wilkinson's polynomial term at char_int. 
    //        Multiply it by the product of previous wilkinsons terms
    //Step 3: Add the values to receive a unique value

    int count = 1;
    unsigned int wilkinsons_value = 1;
    unsigned int *hash_values = unsigned_int_malloc();
    for(int i = 1; i < 21; i ++)
    {
        wilkinsons_value = wilkinsons_value * (char_values[i - 1] - i);
        hash_values[i - 1] = wilkinsons_value;
        printf("Current Hash value is %i\n", hash_values[i - 1]);
    }
    free(char_values);

    //TODO this really ought to be one value
    printf("Hash Value: \n");
    unsigned int hash_sum = 0;
    for(int i = 0; i < LENGTH + 1; i ++)
    {
        hash_sum = hash_sum + hash_values[i];
        printf("The value of %i, is %i\n", i,hash_values[i]);
    }

    printf("Hash Sum is %i\n", hash_sum);

    return hash_sum;
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