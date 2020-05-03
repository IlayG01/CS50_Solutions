#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avarage;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avarage = ((int)image[i][j].rgbtBlue + (int)image[i][j].rgbtRed +
                       (int)image[i][j].rgbtGreen) / (float)3;
            image[i][j].rgbtBlue = round(avarage);
            image[i][j].rgbtGreen = round(avarage);
            image[i][j].rgbtRed = round(avarage);
        }
    }
    return;
}

// Swaping pixels
void swapPixels(RGBTRIPLE *pixel, RGBTRIPLE *pixel2)
{
    RGBTRIPLE holder = *pixel;
    *pixel = *pixel2;
    *pixel2 = holder;
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swapPixels(&image[i][j], &image[i][width - 1 - j]); //same height, different width(mirror)
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize sammary's
            float sumBlue = 0;
            float sumRed = 0;
            float sumGreen = 0;
            int boxCounter = 0;

            for (int k = i - 1; k < i + 2; k++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    if (m != -1 & m != width & k != -1 & k != height)   // Valid pixel
                    {
                        sumBlue += (int)image[k][m].rgbtBlue;
                        sumRed += (int)image[k][m].rgbtRed;
                        sumGreen += (int)image[k][m].rgbtGreen;
                        boxCounter += 1;
                    }
                }
            }
            imageCpy[i][j].rgbtBlue = round(sumBlue / boxCounter);
            imageCpy[i][j].rgbtGreen = round(sumGreen / boxCounter);
            imageCpy[i][j].rgbtRed = round(sumRed / boxCounter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCpy[i][j];
        }
    }
    return;
}

// checking for overflow in pixels
int isOverFlow(int number)
{
    if (number > 255)
    {
        number = 255;
    }
    return number;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCpy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initialize sammary's
            // GY
            int gySumBlue = 0;
            int gySumGreen = 0;
            int gySumRed = 0;
            // GX
            int gxSumBlue = 0;
            int gxSumGreen = 0;
            int gxSumRed = 0;

            // Gy algorithm
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    int multiplier = 0;

                    // Setting the multiplier to the right value
                    if (k == i - 1)
                    {
                        multiplier -= 1;
                    }
                    else if (k == i + 1)
                    {
                        multiplier += 1;
                    }
                    if (m == j)
                    {
                        multiplier = multiplier + multiplier;
                    }


                    // black 1px frame
                    if (m == -1 || m == width || k == -1 || k == height)   // nothing added to sum
                    {
                    }
                    else
                    {
                        gySumBlue += (int)image[k][m].rgbtBlue * multiplier;
                        gySumGreen += (int)image[k][m].rgbtGreen * multiplier;
                        gySumRed += (int)image[k][m].rgbtRed * multiplier;
                    }
                }
            }

            // Gx algorithm
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int m = j - 1; m < j + 2; m++)
                {
                    int multiplier = 0;

                    // Setting the multiplier to the right value
                    if (m == j - 1)
                    {
                        multiplier -= 1;
                    }
                    else if (m == j + 1)
                    {
                        multiplier += 1;
                    }
                    if (k == i)
                    {
                        multiplier = multiplier + multiplier;
                    }


                    // black 1px frame
                    if (m == -1 || m == width || k == -1 || k == height)   // nothing added to sum
                    {
                    }
                    else
                    {
                        gxSumBlue += (int)image[k][m].rgbtBlue * multiplier;
                        gxSumGreen += (int)image[k][m].rgbtGreen * multiplier;
                        gxSumRed += (int)image[k][m].rgbtRed * multiplier;
                    }
                }
            }
            imageCpy[i][j].rgbtBlue = isOverFlow(round(sqrt((gxSumBlue * gxSumBlue) + (gySumBlue * gySumBlue))));
            imageCpy[i][j].rgbtGreen = isOverFlow(round(sqrt((gxSumGreen * gxSumGreen) + (gySumGreen * gySumGreen))));
            imageCpy[i][j].rgbtRed = isOverFlow(round(sqrt((gxSumRed * gxSumRed) + (gySumRed * gySumRed))));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCpy[i][j];
        }
    }
    return;
}
