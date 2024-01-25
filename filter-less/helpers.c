#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            BYTE mean = average(image[row][column]);
            image[row][column].rgbtBlue = mean;
            image[row][column].rgbtGreen = mean;
            image[row][column].rgbtRed = mean;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            make_sepia_pixel(&image[row][column]);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *image_copy = malloc(height*width*sizeof(RGBTRIPLE));
    for(int row = 0; row< height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            // imagecopy[row][width-(column+1)] 2d implementation
            image_copy[width*(row+1)-column-1] = image[row][column];
        }
    }
    for(int row = 0; row < height; row ++){
        for(int column = 0; column < width; column++){
            image[row][column] = image_copy[(width*row) + column];
        }
    }
    free(image_copy);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *image_copy = malloc(height*width*sizeof(RGBTRIPLE));
    for(int row = 0; row < height; row ++){
        for(int column = 0; column < width; column++){
            if (is_corner(height, width, row, column)){

            }




        }
    }



    return;
}

bool is_corner(int height, int width, int current_height_index, int current_width_index){
    int height_index_largest = height-1;
    int width_index_largest = width-1;
    if(current_height_index == 0 | current_height_index == height_index_largest){
        if(current_width_index ==0 | current_width_index == width_index_largest){
            return true;
        }
    }else if (current_width_index ==0 | current_width_index == width_index_largest){
        if(current_height_index ==0 | current_height_index == height_index_largest){
            return true;
        }
    }else{
        return false;
    }
}
int corner_average(int height, int width, int current_height_index, int current_width_index, RGBTRIPLE *pixel_original, RGBTRIPLE *pixel_copy){
    int height_index_largest = height-1;
    int width_index_largest = width-1;
    //Upper Left
    if(current_height_index == 0 & current_width_index == 0){
        RGBTRIPLE original_pixel = *pixel_copy;
        RGBTRIPLE one_to_the_right = *(pixel_copy + 1);
        RGBTRIPLE one_down = *(pixel_copy + ((width*current_height_index + 1 )+current_width_index));
        RGBTRIPLE one_down_one_to_the_right = *(pixel_copy + ((width*current_height_index + 1 )+current_width_index + 1 ));

        BYTE mean_red = hex_cap_and_byte((original_pixel.rgbtRed + one_to_the_right.rgbtRed + one_down.rgbtRed + one_down_one_to_the_right.rgbtRed)/4);
        BYTE mean_green = hex_cap_and_byte((original_pixel.rgbtGreen + one_to_the_right.rgbtGreen + one_down.rgbtGreen + one_down_one_to_the_right.rgbtGreen)/4);
        BYTE mean_blue = hex_cap_and_byte((original_pixel.rgbtBlue + one_to_the_right.rgbtBlue + one_down.rgbtBlue + one_down_one_to_the_right.rgbtBlue)/4);

        pixel_copy->rgbtRed = mean_red;
        pixel_copy->rgbtBlue = mean_blue;
        pixel_copy->rgbtGreen = mean_green;
    //Upper Right
    }else if(current_height_index == 0 & current_width_index==width_index_largest){







    //Lower Left
    }else if(current_height_index == height_index_largest & current_width_index==0){








    }else{
    //Lower Right








    }










}

BYTE average(const RGBTRIPLE pixel)
{
    int sum = pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed;
    int temp = sum/3;
    return hex_cap_and_byte(temp);
}

void make_sepia_pixel(RGBTRIPLE *pixel)
{
    const RGBTRIPLE reference = {.rgbtBlue = pixel->rgbtBlue, .rgbtGreen = pixel->rgbtGreen, .rgbtRed = pixel->rgbtRed};

    BYTE blue = hex_cap_and_byte(.272 * reference.rgbtRed + .534 * reference.rgbtGreen + .131 * reference.rgbtBlue);
    BYTE green = hex_cap_and_byte(.349 * reference.rgbtRed + .686 * reference.rgbtGreen + .168 * reference.rgbtBlue);
    BYTE red = hex_cap_and_byte(.393 * reference.rgbtRed + .769 * reference.rgbtGreen + .189 * reference.rgbtBlue);
    
    pixel->rgbtBlue = blue;
    pixel->rgbtGreen = green;
    pixel->rgbtRed = red;

    return;
}