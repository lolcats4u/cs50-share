// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *word);
unsigned int hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);

//This returns a malloc pointer and does not free
int *array_to_malloc_pointer();
//this returns a pointer to an int and does nto free
int *concatenate_char_value_array(int *char_value_array);
//This returns an unsigned int pointer and does not free
unsigned int *concatenate_ints_in_memory(int *char_values);

#endif // DICTIONARY_H
