#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // adasddas
    // 5asddsasad
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int avg = round((red + green + blue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // adsdasda
    // 1adasdda
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // asddada
    // 1asdasdasddd
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtGreen = green;
            image[i][width - j - 1].rgbtBlue = blue;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    // copying the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img[i][j].rgbtRed = image[i][j].rgbtRed;
            img[i][j].rgbtGreen = image[i][j].rgbtGreen;
            img[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // sdsddsd
    // sdsdds
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red, green, blue;
            float count;

            // checking pixel
            if (i == 0 && j == 0)
            {
                red   = img[i][j].rgbtRed   + img[i + 1][j].rgbtRed   + img[i][j + 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                green = img[i][j].rgbtGreen + img[i + 1][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                blue  = img[i][j].rgbtBlue  + img[i + 1][j].rgbtBlue  + img[i][j + 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
                count = 4.0;
            }
            else if (i == 0 && j == width - 1)  // kbjbjb
            {
                red   = img[i][j].rgbtRed   + img[i][j - 1].rgbtRed   + img[i + 1][j - 1].rgbtRed   + img[i + 1][j].rgbtRed;
                green = img[i][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen;
                blue  = img[i][j].rgbtBlue  + img[i][j - 1].rgbtBlue  + img[i + 1][j - 1].rgbtBlue  + img[i + 1][j].rgbtBlue;
                count = 4.0;
            }
            else if (i == height - 1 && j == 0)     // jkjhkh
            {
                red   = img[i][j].rgbtRed   + img[i - 1][j].rgbtRed   + img[i][j + 1].rgbtRed   + img[i - 1][j + 1].rgbtRed;
                green = img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i][j + 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen;
                blue  = img[i][j].rgbtBlue  + img[i - 1][j].rgbtBlue  + img[i][j + 1].rgbtBlue  + img[i - 1][j + 1].rgbtBlue;
                count = 4.0;
            }
            else if (i == height - 1 && j == width - 1)     //lhkjhkj
            {
                red   = img[i][j].rgbtRed   + img[i - 1][j].rgbtRed   + img[i][j - 1].rgbtRed   + img[i - 1][j - 1].rgbtRed;
                green = img[i][j].rgbtGreen + img[i - 1][j].rgbtGreen + img[i][j - 1].rgbtGreen + img[i - 1][j - 1].rgbtGreen;
                blue  = img[i][j].rgbtBlue  + img[i - 1][j].rgbtBlue  + img[i][j - 1].rgbtBlue  + img[i - 1][j - 1].rgbtBlue;
                count = 4.0;
            }
            else if (i == 0)        //kjkkjb
            {
                red    = img[i][j - 1].rgbtRed   + img[i][j].rgbtRed   + img[i][j + 1].rgbtRed;
                green  = img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen;
                blue   = img[i][j - 1].rgbtBlue  + img[i][j].rgbtBlue  + img[i][j + 1].rgbtBlue;

                red   += img[i + 1][j - 1].rgbtRed   + img[i + 1][j].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                green += img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                blue  += img[i + 1][j - 1].rgbtBlue  + img[i + 1][j].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
                count = 6.0;
            }
            else if (j == 0)        //nkjnknln
            {
                red   = img[i - 1][j].rgbtRed   + img[i][j].rgbtRed   + img[i + 1][j].rgbtRed;
                green = img[i - 1][j].rgbtGreen + img[i][j].rgbtGreen + img[i + 1][j].rgbtGreen;
                blue  = img[i - 1][j].rgbtBlue  + img[i][j].rgbtBlue  + img[i + 1][j].rgbtBlue;

                red   += img[i - 1][j + 1].rgbtRed   + img[i][j + 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                green += img[i - 1][j + 1].rgbtGreen + img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                blue  += img[i - 1][j + 1].rgbtBlue  + img[i][j + 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
                count = 6.0;
            }
            else if (i == height - 1)       //jnkjkb
            {
                red   = img[i][j - 1].rgbtRed   + img[i][j].rgbtRed   + img[i][j + 1].rgbtRed;
                green = img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen;
                blue  = img[i][j - 1].rgbtBlue  + img[i][j].rgbtBlue  + img[i][j + 1].rgbtBlue;

                red   += img[i - 1][j - 1].rgbtRed   + img[i - 1][j].rgbtRed   + img[i - 1][j + 1].rgbtRed;
                green += img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen;
                blue  += img[i - 1][j - 1].rgbtBlue  + img[i - 1][j].rgbtBlue  + img[i - 1][j + 1].rgbtBlue;
                count = 6.0;
            }
            else if (j == width - 1)        //kbjhjhb
            {
                red   = img[i - 1][j].rgbtRed   + img[i][j].rgbtRed   + img[i + 1][j].rgbtRed;
                green = img[i - 1][j].rgbtGreen + img[i][j].rgbtGreen + img[i + 1][j].rgbtGreen;
                blue  = img[i - 1][j].rgbtBlue  + img[i][j].rgbtBlue  + img[i + 1][j].rgbtBlue;

                red   += img[i - 1][j - 1].rgbtRed   + img[i][j - 1].rgbtRed   + img[i + 1][j - 1].rgbtRed;
                green += img[i - 1][j - 1].rgbtGreen + img[i][j - 1].rgbtGreen + img[i + 1][j - 1].rgbtGreen;
                blue  += img[i - 1][j - 1].rgbtBlue  + img[i][j - 1].rgbtBlue  + img[i + 1][j - 1].rgbtBlue;
                count = 6.0;
            }
            else        //hkhljlkj
            {
                red   = img[i - 1][j - 1].rgbtRed   + img[i - 1][j].rgbtRed   + img[i - 1][j + 1].rgbtRed;
                green = img[i - 1][j - 1].rgbtGreen + img[i - 1][j].rgbtGreen + img[i - 1][j + 1].rgbtGreen;
                blue  = img[i - 1][j - 1].rgbtBlue  + img[i - 1][j].rgbtBlue  + img[i - 1][j + 1].rgbtBlue;

                red   += img[i][j - 1].rgbtRed   + img[i][j].rgbtRed   + img[i][j + 1].rgbtRed;
                green += img[i][j - 1].rgbtGreen + img[i][j].rgbtGreen + img[i][j + 1].rgbtGreen;
                blue  += img[i][j - 1].rgbtBlue  + img[i][j].rgbtBlue  + img[i][j + 1].rgbtBlue;

                red   += img[i + 1][j - 1].rgbtRed   + img[i + 1][j].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                green += img[i + 1][j - 1].rgbtGreen + img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                blue  += img[i + 1][j - 1].rgbtBlue  + img[i + 1][j].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
                count = 9.0;
            }

            // sadasdsad
            int blurRed = round(red / count);
            int blurGreen = round(green / count);
            int blurBlue = round(blue / count);

            // adasddas
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtGreen = blurGreen;
            image[i][j].rgbtBlue = blurBlue;
        }
    }
}
