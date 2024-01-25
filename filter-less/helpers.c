#include "helpers.h"
#include <math.h>
#include <stdlib.h>

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
    return;
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