#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void open_memory_card(char *cl_argument);
void int_to_counter(int number_of_jpegs, char* base_counter);
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc == 2){
        open_memory_card(argv[1]);
    }
    else{
        printf("Please include filename");
    }
}

void open_memory_card(char *cl_argument)
{
    int number_of_jpegs_read = 0;
    char file_counter[3] = "000";

    FILE* memory_card_file_stream = fopen(cl_argument, "rb");
    if(memory_card_file_stream != NULL)
    {   
        BYTE buffer_512_bytes[512];
        while(fread(&buffer_512_bytes, sizeof(buffer_512_bytes),1,memory_card_file_stream))
        {
            if(
                buffer_512_bytes[0] == 0xff 
                && buffer_512_bytes[1] == 0xd8 
                && buffer_512_bytes[2] == 0xff 
                && (buffer_512_bytes[3] & 0xf0) == 0xe0
                )
                {
                    int_to_counter(number_of_jpegs_read, file_counter);
                    FILE *new_jpeg = fopen(file_counter, "wb");
                    if(new_jpeg != NULL){
                        fwrite(buffer_512_bytes,sizeof(buffer_512_bytes[0]), 512, new_jpeg);
                        fclose(new_jpeg);
                        number_of_jpegs_read++;
                    }
                    else{
                        fclose(memory_card_file_stream);
                        fclose(new_jpeg);
                        printf("New jpeg not created\n");
                    }
                }
        }
    }else if(feof(memory_card_file_stream)){
        fclose(memory_card_file_stream);
        printf("Reached end of card\n");
    }
    else{
        printf("File %s not found", cl_argument);
    }
}

void int_to_counter(int number_of_jpegs, char* base_counter)
{
    if(number_of_jpegs < 10){
        //int to ascii conversion
        base_counter[2] = number_of_jpegs + 48;
        base_counter[1] = 48;
        base_counter[0] = 48;
    }else if ( 10 <= number_of_jpegs && number_of_jpegs <= 99){
        while (number_of_jpegs != 0){
            base_counter[0] = 48;
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
}