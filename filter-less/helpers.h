#include "bmp.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]);

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]);

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]);

// Average pixel values
int average(const RGBTRIPLE pixel);

// Performs Sepia Calculation on Pixel
void make_sepia_pixel(RGBTRIPLE *pixel);

// BYTE type caps number at 255
BYTE hex_cap_and_byte(double value);