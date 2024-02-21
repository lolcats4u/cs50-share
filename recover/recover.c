#include <stdio.h>
#include <stdlib.h>
int open_memory_card();
int int_to_counter(int number_of_jpegs);
int main(int argc, char *argv[])
{
    open_memory_card(argv[1]);
}

int open_memory_card(char *cl_argument)
{
    int number_of_jpegs_read = 0;
    FILE* memory_card_file_stream = fopen(cl_argument, "r");
    if(memory_card_file_stream != NULL)
    {   
        char buffer_512_bytes[512];
        while(fread(&buffer_512_bytes, sizeof(buffer_512_bytes),1,memory_card_file_stream))
        {

            if(
                buffer_512_bytes[0] == 0xff 
                && buffer_512_bytes[1] == 0xd8 
                && buffer_512_bytes [2] == 0xff 
                && (buffer_512_bytes[3] & 0xf0) == 0xe0
                )
                {
                    FILE *new_jpeg = fopen(int_to_counter(number_of_jpegs_read), "w");
                    if(new_jpeg == NULL)
                    {
                        fclose(new_jpeg);
                        return 1;
                    }
                    number_of_jpegs_read++;
                }

        }

    }
}

char int_to_counter(int number_of_jpegs)
{
    char* base_counter = "000";
    if(number_of_jpegs < 10){
        //int to ascii conversion
        base_counter[2] = number_of_jpegs + 48;
    }else if ( 10 <= number_of_jpegs <= 99){
        while (number_of_jpegs != 0){
            base_counter[1] = (number_of_jpegs % 10) + 48;
            base_counter[2] = (number_of_jpegs - ((number_of_jpegs % 10) * 10)) + 48;
        }
    }else
    {
        int ones_place = number_of_jpegs /100;
        int tens_place = (number_of_jpegs/10) - ones_place;
        int hundreds_place = number_of_jpegs - ones_place - tens_place;
        base_counter[0] = hundreds_place;
        base_counter[1] = tens_place;
        base_counter[2] = ones_place;
    }
    return base_counter;
}
