#include "bmp.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// Average pixel values
BYTE average(const RGBTRIPLE pixel);

// Performs Sepia Calculation on Pixel
void make_sepia_pixel(RGBTRIPLE *pixel);

//Is a given 2d index on the corner of an array
bool is_corner(int height, int width, int current_height_index, int current_width_index);

//Calculate the average of the RGB values of a corner pixel
int corner_average(int height, int width, int current_height_index, int current_width_index, RGBTRIPLE);

int oned_index_math(int width, int row_index, int column_index);

RGBTRIPLE make_blurred_pixel(int number_of_pixels, RGBTRIPLE pixel_array[number_of_pixels]);

// BYTE type caps number at 255
static inline BYTE hex_cap_and_byte(double value)
{
    if (value > 255.0)
    {
        return (BYTE) 255;
    }
    else
    {
        return round((BYTE) value);
    }
}