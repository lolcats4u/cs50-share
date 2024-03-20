#include <stdbool.h>
#include <stdio.h>
#include <fcntl.h>
bool load(const char *dictionary);
int main()
{
    char *file_path = "/Users/mherl/Documents/cs50-share/speller/speller_test/small_dict";
    load(file_path);
    return 0;
}

bool load(const char *dictionary)
{
    // TODO
    int chonk[512];
    size_t bytes_read = 0;
    FILE *fptr;

    int file = fopen(dictionary, "rb");

    if (fptr != NULL)
    {
        while ((bytes_read = fread(chonk, 1, sizeof(chonk), file)) > 0)
        {
            printf("%c",file);
        }
    }

    return false;
}
