#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 45
int concatenate(int number1, int number2);
unsigned int hash(const char *word);

//This returns a malloc pointer and does not free
int *array_to_malloc_pointer();
unsigned int concatenate_ints_in_memory(int *char_values);


int main()
{
    const char *word = "some_word";
    unsigned int hash_value = hash(word);
    printf("%c\n", *word);
    printf("%d\n", hash_value);


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
    int *char_values = array_to_malloc_pointer();


    //Determine the int value of each character.
    //Assign that int value to the char_values memory
    for(int i = 0; i < LENGTH; i++)
    {
        char_values[i] = toupper(word[i]);
    }

    //concatenate all of the ascii char ints into a single int
    unsigned int char_int = concatenate_ints_in_memory(char_values);

    //free the memory used for char values
    free(char_values);

    //I used http://www.cs.cmu.edu/afs/cs/academic/class/15210-s15/www/lectures/hash-notes.pdf
    //as inspiration for this hash because it was a little more 
    //friendly than http://math.uchicago.edu/~may/REU2020/REUPapers/Miller.pdf

    //I went down a rabbit hole looking at cool polynomials, but I have a hard time reading formal
    //notation so lets just call this my "interpretation" of wilkinson's polynomial evaluated at 
    //char_int

    //Step 1: Evaluate a wilkinson's polynomial term at char_int. 
    //        Multiply it by the product of previous wilkinsons terms
    //step 2: Mod this value with 3 *its almost pi day 🥧*
    //Step 4: Concatenate the mod values to receive a unique value

    int count = 1;
    unsigned int wilkinsons_value = 1;
    int hash_value = 0;
    int *hash_array = array_to_malloc_pointer();
    while (count < 21)
    {
        wilkinsons_value = wilkinsons_value * (char_int - count);
        hash_array[count - 1] =  (wilkinsons_value % 3);
        count ++;
    }
    hash_value = concatenate_ints_in_memory(hash_array);

    //TODO make sure this is sufficiently unique
    printf("Hash value %d", hash_value);

    return hash_value;
}

int *array_to_malloc_pointer()
{
    const int size_char_array = sizeof(char) * (LENGTH + 1);
    int *array_to_heap = malloc(size_char_array);
    //initialize memory strip to 0🧹
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