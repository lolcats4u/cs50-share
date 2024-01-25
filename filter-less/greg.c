#include "helpers.h"
#include "bmp.h"

void blur(int height, int width, RGBTRIPLE[height][width]);
static inline 


void blur(int height, int width, RGBTRIPLE[height][width] iamge)
{
    RGBTRIPLE* image_copy = malloc(width*height*sizeof(RGBTRIPLE));

    if (image_copy == NULL)
    {
        return;
    }
    

    RGBTRIPLE[9] temp_array;
    // First pixel
    temp_array[0] = image_copy[0];
    temp_array[1] = image_copy[1];
    temp_array[2] = image_copy[width];
    temp_array[3] = image_copy[width+1];
    image[0][0] = average_color(4, temp_array);

    // First row
    for(int col = 1; col < width - 1; col++)
    {
        temp_array[0] = image_copy[col-1];
        temp_array[1] = image_copy[col];
        temp_array[2] = image_copy[col+1];
        temp_array[3] = image_copy[width+col-1];
        temp_array[4] = image_copy[width+col];
        temp_array[5] = image_copy[width+col+1];
        image[0][col] = average_color(6, temp_array);
    }
    // Last pixel, first row
    temp_array[0] = image_copy[width-2];
    temp_array[1] = image_copy[width-1];
    temp_array[2] = image_copy[2*width-2];
    temp_array[3] = image_copy[2*width-1];
    image[0][width-1] = average_color(4, temp_array);

    // Middle rows
    int row1;
    int row2;
    int row3;
    for(int row = 1; row < height - 1; row++)
    {
        current_pixel = row*width;
        temp_array[0] = image_copy[current_pixel-width];
        temp_array[1] = image_copy[current_pixel-width+1];
        temp_array[2] = image_copy[current_pixel];
        temp_array[3] = image_copy[current_pixel+1];
        temp_array[4] = image_copy[current_pixel+width];
        temp_array[5] = image_copy[current_pixel+width+1];
        image[row][0] = average_color(6, temp_array);

        row1 = (row-1)*width;
        row2 = row1 + width;
        row3 = row2 + width;
        for(int col = 1; col < width - 1; col++)
        {
            temp_array[0] = image_copy[row1];
            temp_array[1] = image_copy[row1+1];
            temp_array[2] = image_copy[row1+2];
            temp_array[3] = image_copy[row2];
            temp_array[4] = image_copy[row2+1];
            temp_array[5] = image_copy[row2+2];
            temp_array[6] = image_copy[row3];
            temp_array[7] = image_copy[row3+1];
            temp_array[8] = image_copy[row3+2];
            image[row][col] = average_color(9, temp_array);
            row1++;
            row2++;
            row3++;
        }

        current_pixel = (row+1)*width-1;
        temp_array[0] = image_copy[current_pixel-width];
        temp_array[1] = image_copy[current_pixel-width-1];
        temp_array[2] = image_copy[current_pixel-1];
        temp_array[3] = image_copy[current_pixel];
        temp_array[4] = image_copy[current_pixel+width];
        temp_array[5] = image_copy[current_pixel+width-1];
        image[row][width-1] = average_color(6,temp_array);
    }

    // TODO: Last row

    free(image_copy);
    return;
}

RGBTRIPLE average_color(int num_pixels, RGBTRIPLE[num_pixels] array)
{
    int red = 0;
    int green = 0;
    int blue = 0;
    for(int i = 0; i < num_pixels; i++)
    {
        red = red + array[i].rgbtRed;
        green = green + array[i].rgbtGreen;
        blue = blue + array[i].rgbtBlue;
    }
    red = red / num_pixels;
    green = green / num_pixels;
    blue = blue / num_pixels;
    RGBTRIPLE result = {.rgbtRed = red, .rgbtGreen = green, .rgbtBlue = blue};
    return result;
}