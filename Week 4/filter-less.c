#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);

            image[h][w].rgbtBlue = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int calcR = round((image[h][w].rgbtRed * .393) + (image[h][w].rgbtGreen * .769) + (image[h][w].rgbtBlue * .189));
            int calcG = round((image[h][w].rgbtRed * .349) + (image[h][w].rgbtGreen * .686) + (image[h][w].rgbtBlue * .168));
            int calcB = round((image[h][w].rgbtRed * .272) + (image[h][w].rgbtGreen * .534) + (image[h][w].rgbtBlue * .131));

            // Color’s value is no higher than 255
            if (calcR > 255)
            {
                calcR = 255;
            }
            if (calcG > 255)
            {
                calcG = 255;
            }
            if (calcB > 255)
            {
                calcB = 255;
            }

            image[h][w].rgbtRed = calcR;
            image[h][w].rgbtGreen = calcG;
            image[h][w].rgbtBlue = calcB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - 1 - w];
            image[h][width - 1 - w] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy image
    RGBTRIPLE copy[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            copy[h][w] = image[h][w];
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float count = 0.0;
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // Find neighbour points
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int pointX = h + x;
                    int pointY = w + y;

                    // Check allowed confinse
                    if (pointX < 0 || pointY < 0 || pointX > (height - 1) || pointY > (width - 1))
                    {
                        continue;
                    }

                    count ++;
                    sumRed += image[pointX][pointY].rgbtRed;
                    sumGreen += image[pointX][pointY].rgbtGreen;
                    sumBlue += image[pointX][pointY].rgbtBlue;
                }
            }

            // Calculate average points
            copy[h][w].rgbtRed = round(sumRed / count);
            copy[h][w].rgbtGreen = round(sumGreen / count);
            copy[h][w].rgbtBlue = round(sumBlue / count);
        }
    }

    // Copy changes to original image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = copy[h][w].rgbtRed;
            image[h][w].rgbtGreen = copy[h][w].rgbtGreen;
            image[h][w].rgbtBlue = copy[h][w].rgbtBlue;
        }
    }
    return;
}