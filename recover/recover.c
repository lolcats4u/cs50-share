#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

void open_memory_card(char *cl_argument);
void int_to_counter(int number_of_jpegs, char* base_counter);
typedef uint8_t BYTE;
bool jpeg_header_bool(BYTE* buffer);

int main(int argc, char *argv[])
{
    if(argc == 2){
        open_memory_card(argv[1]);
    }
    else{
        printf("Please include filename");
    }
}

int open_memory_card(char *cl_argument)
{
    // return 1; 
    // failed to open new jpeg file;

    //return2;
    //bad cla
    int number_of_jpegs_read = 0;
    char file_counter[8] = "000.jpg";

    FILE* memory_card_file_stream = fopen(cl_argument, "rb");
    if(memory_card_file_stream != NULL)
    {   
        BYTE buffer_512_bytes[512];
        FILE *new_jpeg;
        bool file_is_open = false;
        while(fread(&buffer_512_bytes, sizeof(buffer_512_bytes),1,memory_card_file_stream))
        {
            if(file_is_open && jpeg_header_bool(buffer_512_bytes)){
                fclose(new_jpeg);
                number_of_jpegs_read++;
                file_is_open = false;
            }
            if(jpeg_header_bool(buffer_512_bytes) && !file_is_open){
                int_to_counter(number_of_jpegs_read, file_counter);
                new_jpeg = fopen(file_counter, "wb");
                if(new_jpeg != NULL){
                    file_is_open = true;
                }else{
                    printf("Jpeg failed to open");
                    return 1;
                }
            }
            if(file_is_open){
                fwrite(buffer_512_bytes,sizeof(buffer_512_bytes[0]),512, new_jpeg);
            }
        }return 0;
    }
    else if(feof(memory_card_file_stream)){
        fclose(memory_card_file_stream);
        printf("Reached end of card\n");
        return 0;
    }
    else{
        printf("File %s not found", cl_argument);
        return 2;
    }
}

void int_to_counter(int number_of_jpegs, char* base_counter)
{
        int hundreds_place = number_of_jpegs /100;
        int tens_place = (number_of_jpegs-hundreds_place*100)/10;
        int ones_place = number_of_jpegs - hundreds_place*100 - tens_place*10;
        base_counter[0] = hundreds_place +48;
        base_counter[1] = tens_place +48;
        base_counter[2] = ones_place +48;
}

bool jpeg_header_bool(BYTE* buffer){
    if(
        buffer[0] == 0xff 
        && buffer[1] == 0xd8 
        && buffer[2] == 0xff 
        && (buffer[3] & 0xf0) == 0xe0)
        {
            return true;
        }
    return false;
}