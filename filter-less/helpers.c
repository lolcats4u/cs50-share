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
    }return false;
}
int blur_corner(int height, int width, int current_height_index, int current_width_index, int oned_index, RGBTRIPLE *image_copy[oned_index], RGBTRIPLE *original_image[current_height_index][current_width_index]){
    int height_index_largest = height-1;
    int width_index_largest = width-1;
    //Upper Left
    if(current_height_index == 0 & current_width_index == 0){
        RGBTRIPLE original_pixel = *image_copy[oned_index_math(width, current_height_index, current_width_index)];
        RGBTRIPLE one_to_the_right = *image_copy[oned_index_math(width, current_height_index, current_width_index + 1)];
        RGBTRIPLE one_down = *image_copy[oned_index_math(width, current_height_index + 1, current_width_index)];
        RGBTRIPLE one_down_one_to_the_right = *image_copy[oned_index_math(width, current_height_index + 1, current_width_index + 1)];

        RGBTRIPLE blur_pixel_fodder [] = {original_pixel, one_to_the_right, one_down, one_down_one_to_the_right};

        RGBTRIPLE new_blurred_pixel = make_blurred_pixel(4, blur_pixel_fodder);

        original_image[current_height_index][current_width_index]->rgbtRed = new_blurred_pixel.rgbtRed;
        original_image[current_height_index][current_width_index]->rgbtGreen = new_blurred_pixel.rgbtGreen;
        original_image[current_height_index][current_width_index]->rgbtBlue = new_blurred_pixel.rgbtBlue;


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

RGBTRIPLE make_blurred_pixel(int number_of_pixels, RGBTRIPLE pixel_array[number_of_pixels]){
    RGBTRIPLE new_pixel;
    int red_buffer = 0;
    int green_buffer = 0;
    int blue_buffer = 0;
    for(int i = 0; i < number_of_pixels -1; i++){
        red_buffer = red_buffer + pixel_array[i].rgbtRed;
        green_buffer = green_buffer + pixel_array[i].rgbtGreen;
        blue_buffer = blue_buffer + pixel_array[i].rgbtBlue;
    }
    red_buffer = round(red_buffer/number_of_pixels);
    green_buffer = round(green_buffer/number_of_pixels);
    blue_buffer = round(blue_buffer/number_of_pixels);

    new_pixel.rgbtRed = red_buffer;
    new_pixel.rgbtGreen = green_buffer;
    new_pixel.rgbtBlue = blue_buffer;

    return new_pixel;
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

int oned_index_math(int width, int row_index, int column_index){
    return ((width*row_index) + column_index);
}