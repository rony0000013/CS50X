#include "helpers.h"
#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            int gxred, gxgreen, gxblue, gyred, gygreen, gyblue;

            // checking pixel
            if (i == 0 && j == 0)
            {
                gxred   = 2 * img[i][j + 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gxgreen = 2 * img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gxblue  = 2 * img[i][j + 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;

                gyred   = 2 * img[i + 1][j].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gygreen = 2 * img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gyblue  = 2 * img[i + 1][j].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
            }
            else if (i == 0 && j == width - 1)  // kbjbjb
            {
                gxred   = -2 * img[i][j - 1].rgbtRed   + -1 * img[i + 1][j - 1].rgbtRed;
                gxgreen = -2 * img[i][j - 1].rgbtGreen + -1 * img[i + 1][j - 1].rgbtGreen;
                gxblue  = -2 * img[i][j - 1].rgbtBlue  + -1 * img[i + 1][j - 1].rgbtBlue;

                gyred   = 2 * img[i + 1][j].rgbtRed   + img[i + 1][j - 1].rgbtRed;
                gygreen = 2 * img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen;
                gyblue  = 2 * img[i + 1][j].rgbtBlue  + img[i + 1][j - 1].rgbtBlue;
            }
            else if (i == height - 1 && j == 0)     // jkjhkh
            {
                gxred   = 2 * img[i][j + 1].rgbtRed   + img[i - 1][j + 1].rgbtRed;
                gxgreen = 2 * img[i][j + 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen;
                gxblue  = 2 * img[i][j + 1].rgbtBlue  + img[i - 1][j + 1].rgbtBlue;

                gyred   = -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j + 1].rgbtRed;
                gygreen = -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j + 1].rgbtGreen;
                gyblue  = -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j + 1].rgbtBlue;
            }
            else if (i == height - 1 && j == width - 1)     //lhkjhkj
            {
                gxred   = -2 * img[i][j - 1].rgbtRed   + -1 * img[i - 1][j - 1].rgbtRed;
                gxgreen = -2 * img[i][j - 1].rgbtGreen + -1 * img[i - 1][j - 1].rgbtGreen;
                gxblue  = -2 * img[i][j - 1].rgbtBlue  + -1 * img[i - 1][j - 1].rgbtBlue;

                gyred   = -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j - 1].rgbtRed;
                gygreen = -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j - 1].rgbtGreen;
                gyblue  = -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j - 1].rgbtBlue;
            }
            else if (i == 0)        //kjkkjb
            {
                gxred    = -2 * img[i][j - 1].rgbtRed   + 2 * img[i][j + 1].rgbtRed   + -1 * img[i + 1][j - 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gxgreen  = -2 * img[i][j - 1].rgbtGreen + 2 * img[i][j + 1].rgbtGreen + -1 * img[i + 1][j - 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gxblue   = -2 * img[i][j - 1].rgbtBlue  + 2 * img[i][j + 1].rgbtBlue  + -1 * img[i + 1][j - 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;

                gyred    = img[i + 1][j - 1].rgbtRed   + 2 * img[i + 1][j].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gygreen  = img[i + 1][j - 1].rgbtGreen + 2 * img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gyblue   = img[i + 1][j - 1].rgbtBlue  + 2 * img[i + 1][j].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
            }
            else if (j == 0)        //nkjnknln
            {
                gxred    = img[i - 1][j + 1].rgbtRed   + 2 * img[i][j + 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gxgreen  = img[i - 1][j + 1].rgbtGreen + 2 * img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gxblue   = img[i - 1][j + 1].rgbtBlue  + 2 * img[i][j + 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;

                gyred    = -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j + 1].rgbtRed   + 2 * img[i + 1][j].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gygreen  = -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j + 1].rgbtGreen + 2 * img[i + 1][j].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gyblue   = -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j + 1].rgbtBlue  + 2 * img[i + 1][j].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;
            }
            else if (i == height - 1)       //jnkjkb
            {
                gxred    = -2 * img[i][j - 1].rgbtRed   + 2 * img[i][j + 1].rgbtRed   + -1 * img[i - 1][j - 1].rgbtRed   + img[i - 1][j + 1].rgbtRed;
                gxgreen  = -2 * img[i][j - 1].rgbtGreen + 2 * img[i][j + 1].rgbtGreen + -1 * img[i - 1][j - 1].rgbtGreen + img[i - 1][j + 1].rgbtGreen;
                gxblue   = -2 * img[i][j - 1].rgbtBlue  + 2 * img[i][j + 1].rgbtBlue  + -1 * img[i - 1][j - 1].rgbtBlue  + img[i - 1][j + 1].rgbtBlue;

                gyred    = -1 * img[i - 1][j - 1].rgbtRed   + -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j + 1].rgbtRed;
                gygreen  = -1 * img[i - 1][j - 1].rgbtGreen + -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j + 1].rgbtGreen;
                gyblue   = -1 * img[i - 1][j - 1].rgbtBlue  + -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j + 1].rgbtBlue;
            }
            else if (j == width - 1)        //kbjhjhb
            {
                gxred    = -1 * img[i - 1][j - 1].rgbtRed   + -2 * img[i][j - 1].rgbtRed   + -1 * img[i + 1][j - 1].rgbtRed;
                gxgreen  = -1 * img[i - 1][j - 1].rgbtGreen + -2 * img[i][j - 1].rgbtGreen + -1 * img[i + 1][j - 1].rgbtGreen;
                gxblue   = -1 * img[i - 1][j - 1].rgbtBlue  + -2 * img[i][j - 1].rgbtBlue  + -1 * img[i + 1][j - 1].rgbtBlue;

                gyred    = -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j - 1].rgbtRed   + 2 * img[i + 1][j].rgbtRed   + img[i + 1][j - 1].rgbtRed;
                gygreen  = -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j - 1].rgbtGreen + 2 * img[i + 1][j].rgbtGreen + img[i + 1][j - 1].rgbtGreen;
                gyblue   = -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j - 1].rgbtBlue  + 2 * img[i + 1][j].rgbtBlue  + img[i + 1][j - 1].rgbtBlue;
            }
            else        //hkhljlkj
            {
                gxred    = -1 * img[i - 1][j - 1].rgbtRed   + -2 * img[i][j - 1].rgbtRed   + -1 * img[i + 1][j - 1].rgbtRed;
                gxgreen  = -1 * img[i - 1][j - 1].rgbtGreen + -2 * img[i][j - 1].rgbtGreen + -1 * img[i + 1][j - 1].rgbtGreen;
                gxblue   = -1 * img[i - 1][j - 1].rgbtBlue  + -2 * img[i][j - 1].rgbtBlue  + -1 * img[i + 1][j - 1].rgbtBlue;

                gxred    += img[i - 1][j + 1].rgbtRed   + 2 * img[i][j + 1].rgbtRed   + img[i + 1][j + 1].rgbtRed;
                gxgreen  += img[i - 1][j + 1].rgbtGreen + 2 * img[i][j + 1].rgbtGreen + img[i + 1][j + 1].rgbtGreen;
                gxblue   += img[i - 1][j + 1].rgbtBlue  + 2 * img[i][j + 1].rgbtBlue  + img[i + 1][j + 1].rgbtBlue;

                gyred    = -1 * img[i - 1][j - 1].rgbtRed   + -2 * img[i - 1][j].rgbtRed   + -1 * img[i - 1][j + 1].rgbtRed;
                gygreen  = -1 * img[i - 1][j - 1].rgbtGreen + -2 * img[i - 1][j].rgbtGreen + -1 * img[i - 1][j + 1].rgbtGreen;
                gyblue   = -1 * img[i - 1][j - 1].rgbtBlue  + -2 * img[i - 1][j].rgbtBlue  + -1 * img[i - 1][j + 1].rgbtBlue;

                gyred    += 1 * img[i + 1][j - 1].rgbtRed   + 2 * img[i + 1][j].rgbtRed   + 1 * img[i + 1][j + 1].rgbtRed;
                gygreen  += 1 * img[i + 1][j - 1].rgbtGreen + 2 * img[i + 1][j].rgbtGreen + 1 * img[i + 1][j + 1].rgbtGreen;
                gyblue   += 1 * img[i + 1][j - 1].rgbtBlue  + 2 * img[i + 1][j].rgbtBlue  + 1 * img[i + 1][j + 1].rgbtBlue;
            }

            // sadasdsad
            int red = round(pow(pow(gxred, 2.0) + pow(gyred, 2.0), 0.5));
            int green = round(pow(pow(gxgreen, 2.0) + pow(gygreen, 2.0), 0.5));
            int blue = round(pow(pow(gxblue, 2.0) + pow(gyblue, 2.0), 0.5));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // adasddas
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}
