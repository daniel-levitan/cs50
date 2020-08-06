#include "helpers.h"
#include <math.h>

#include <stdio.h>

int calc_sobel(int i, int j, char component, int height, int width, RGBTRIPLE image[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE pixel;

    // leveling all RBG pixels to the average among them. This preserves the brightness.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = pixel;
            image[i][j].rgbtGreen = pixel;
            image[i][j].rgbtRed = pixel;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;

    // changing the position horizontally, e.g., against the y axis
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // aux image
    RGBTRIPLE aux[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // center
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j - 1].rgbtBlue + aux[i - 1][j].rgbtBlue + aux[i - 1][j + 1].rgbtBlue
                                              + aux[i][j - 1].rgbtBlue   + aux[i][j].rgbtBlue   + aux[i][j + 1].rgbtBlue
                                              + aux[i + 1][j - 1].rgbtBlue + aux[i + 1][j].rgbtBlue + aux[i + 1][j + 1].rgbtBlue) / 9.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j - 1].rgbtGreen + aux[i - 1][j].rgbtGreen + aux[i - 1][j + 1].rgbtGreen
                                               + aux[i][j - 1].rgbtGreen   + aux[i][j].rgbtGreen   + aux[i][j + 1].rgbtGreen
                                               + aux[i + 1][j - 1].rgbtGreen + aux[i + 1][j].rgbtGreen + aux[i + 1][j + 1].rgbtGreen) / 9.0);

                image[i][j].rgbtRed = round((aux[i - 1][j - 1].rgbtRed + aux[i - 1][j].rgbtRed + aux[i - 1][j + 1].rgbtRed
                                             + aux[i][j - 1].rgbtRed   + aux[i][j].rgbtRed   + aux[i][j + 1].rgbtRed
                                             + aux[i + 1][j - 1].rgbtRed + aux[i + 1][j].rgbtRed + aux[i + 1][j + 1].rgbtRed) / 9.0);
            }

            // top edge
            if (i == 0 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i][j - 1].rgbtBlue   + aux[i][j].rgbtBlue   + aux[i][j + 1].rgbtBlue
                                              + aux[i + 1][j - 1].rgbtBlue + aux[i + 1][j].rgbtBlue + aux[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtGreen = round((aux[i][j - 1].rgbtGreen   + aux[i][j].rgbtGreen   + aux[i][j + 1].rgbtGreen
                                               + aux[i + 1][j - 1].rgbtGreen + aux[i + 1][j].rgbtGreen + aux[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = round((aux[i][j - 1].rgbtRed   + aux[i][j].rgbtRed   + aux[i][j + 1].rgbtRed
                                             + aux[i + 1][j - 1].rgbtRed + aux[i + 1][j].rgbtRed + aux[i + 1][j + 1].rgbtRed) / 6.0);
            }

            // bottom edge
            if (i == height - 1 && j > 0 && j < width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j - 1].rgbtBlue + aux[i - 1][j].rgbtBlue + aux[i - 1][j + 1].rgbtBlue
                                              + aux[i][j - 1].rgbtBlue   + aux[i][j].rgbtBlue   + aux[i][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j - 1].rgbtGreen + aux[i - 1][j].rgbtGreen + aux[i - 1][j + 1].rgbtGreen
                                               + aux[i][j - 1].rgbtGreen   + aux[i][j].rgbtGreen   + aux[i][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = round((aux[i - 1][j - 1].rgbtRed + aux[i - 1][j].rgbtRed + aux[i - 1][j + 1].rgbtRed
                                             + aux[i][j - 1].rgbtRed   + aux[i][j].rgbtRed   + aux[i][j + 1].rgbtRed) / 6.0);
            }

            // left edge
            if (i > 0 && i < height - 1 && j == 0)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j].rgbtBlue + aux[i][j].rgbtBlue + aux[i + 1][j].rgbtBlue
                                              + aux[i - 1][j + 1].rgbtBlue + aux[i][j + 1].rgbtBlue + aux[i + 1][j + 1].rgbtBlue) / 6.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j].rgbtGreen + aux[i][j].rgbtGreen + aux[i + 1][j].rgbtGreen
                                               + aux[i - 1][j + 1].rgbtGreen + aux[i][j + 1].rgbtGreen + aux[i + 1][j + 1].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = round((aux[i - 1][j].rgbtRed + aux[i][j].rgbtRed + aux[i + 1][j].rgbtRed
                                             + aux[i - 1][j + 1].rgbtRed + aux[i][j + 1].rgbtRed + aux[i + 1][j + 1].rgbtRed) / 6.0);
            }

            // right edge
            if (i > 0 && i < height - 1 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j - 1].rgbtBlue + aux[i - 1][j].rgbtBlue
                                              + aux[i][j - 1].rgbtBlue + aux[i][j].rgbtBlue
                                              + aux[i + 1][j - 1].rgbtBlue + aux[i + 1][j].rgbtBlue) / 6.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j - 1].rgbtGreen + aux[i - 1][j].rgbtGreen
                                               + aux[i][j - 1].rgbtGreen + aux[i][j].rgbtGreen
                                               + aux[i + 1][j - 1].rgbtGreen + aux[i + 1][j].rgbtGreen) / 6.0);

                image[i][j].rgbtRed = round((aux[i - 1][j - 1].rgbtRed + aux[i - 1][j].rgbtRed
                                             + aux[i][j - 1].rgbtRed + aux[i][j].rgbtRed
                                             + aux[i + 1][j - 1].rgbtRed + aux[i + 1][j].rgbtRed) / 6.0);
            }

            // top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue = round((aux[i][j].rgbtBlue + aux[i][j + 1].rgbtBlue
                                              + aux[i + 1][j].rgbtBlue + aux[i + 1][j + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtGreen = round((aux[i][j].rgbtGreen + aux[i][j + 1].rgbtGreen
                                               + aux[i + 1][j].rgbtGreen + aux[i + 1][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = round((aux[i][j].rgbtRed + aux[i][j + 1].rgbtRed
                                             + aux[i + 1][j].rgbtRed + aux[i + 1][j + 1].rgbtRed) / 4.0);
            }

            // top right corner
            if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i][j - 1].rgbtBlue + aux[i][j].rgbtBlue
                                              + aux[i + 1][j - 1].rgbtBlue + aux[i + 1][j].rgbtBlue) / 4.0);

                image[i][j].rgbtGreen = round((aux[i][j - 1].rgbtGreen + aux[i][j].rgbtGreen
                                               + aux[i + 1][j - 1].rgbtGreen + aux[i + 1][j].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = round((aux[i][j - 1].rgbtRed + aux[i][j].rgbtRed
                                             + aux[i + 1][j - 1].rgbtRed + aux[i + 1][j].rgbtRed) / 4.0);
            }

            // bottom left corner
            if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j].rgbtBlue   + aux[i - 1][j + 1].rgbtBlue
                                              + aux[i][j].rgbtBlue + aux[i][j + 1].rgbtBlue) / 4.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j].rgbtGreen   + aux[i - 1][j + 1].rgbtGreen
                                               + aux[i][j].rgbtGreen + aux[i][j + 1].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = round((aux[i - 1][j].rgbtRed   + aux[i - 1][j + 1].rgbtRed
                                             + aux[i][j].rgbtRed + aux[i][j + 1].rgbtRed) / 4.0);
            }

            // bottom right corner
            if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((aux[i - 1][j - 1].rgbtBlue + aux[i][j - 1].rgbtBlue
                                              + aux[i - 1][j].rgbtBlue + aux[i][j].rgbtBlue) / 4.0);

                image[i][j].rgbtGreen = round((aux[i - 1][j - 1].rgbtGreen + aux[i][j - 1].rgbtGreen
                                               + aux[i - 1][j].rgbtGreen + aux[i][j].rgbtGreen) / 4.0);

                image[i][j].rgbtRed = round((aux[i - 1][j - 1].rgbtRed + aux[i][j - 1].rgbtRed
                                             + aux[i - 1][j].rgbtRed   + aux[i][j].rgbtRed) / 4.0);
            }
        }
    }
    return;
}

int calc_sobel(int i, int j, char component, int height, int width, RGBTRIPLE image[height][width])
{
    // components are either r, b, or g
    // x and y kernels are declared, as well as the two components
    float Gx[3][3] = {{-1.0, 0, 1.0},
                      {-2.0, 0, 2.0},
                      {-1.0, 0, 1.0}};

    float Gy[3][3] = {{-1.0, -2.0, -1.0},
                        { 0,  0,  0},
                      { 1.0,  2.0,  1.0}};

    int x_comp = 0;
    int y_comp = 0;

    // center
    if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
    {
        if (component == 'b')
        {
            x_comp =    image[i - 1][j - 1].rgbtBlue * Gx[0][0] + image[i - 1][j + 1].rgbtBlue * Gx[0][2]
                      + image[i]    [j - 1].rgbtBlue * Gx[1][0] + image[i]    [j + 1].rgbtBlue * Gx[1][2]
                      + image[i + 1][j - 1].rgbtBlue * Gx[2][0] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];

            y_comp =    image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2]
                      + image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
        }
        if (component == 'g')
        {
            x_comp =    image[i - 1][j - 1].rgbtGreen * Gx[0][0] + image[i - 1][j + 1].rgbtGreen * Gx[0][2]
                      + image[i]    [j - 1].rgbtGreen * Gx[1][0] + image[i]    [j + 1].rgbtGreen * Gx[1][2]
                      + image[i + 1][j - 1].rgbtGreen * Gx[2][0] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];

            y_comp =    image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2]
                      + image[i + 1][j - 1].rgbtGreen * Gy[2][0] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
        }
        if (component == 'r')
        {
            x_comp =    image[i - 1][j - 1].rgbtRed * Gx[0][0] + image[i - 1][j + 1].rgbtRed * Gx[0][2]
                      + image[i]    [j - 1].rgbtRed * Gx[1][0] + image[i]    [j + 1].rgbtRed * Gx[1][2]
                      + image[i + 1][j - 1].rgbtRed * Gx[2][0] + image[i + 1][j + 1].rgbtRed * Gx[2][2];

            y_comp =    image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2]
                      + image[i + 1][j - 1].rgbtRed * Gy[2][0] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];
        }
    }

    // top left corner
    if (i == 0 && j == 0)
    {
        if (component == 'b')
        {
            x_comp = image[i]    [j + 1].rgbtBlue * Gx[1][2]
                   + image[i + 1][j + 1].rgbtBlue * Gx[2][2];

            y_comp = image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
        }

        if (component == 'g')
        {
            x_comp = image[i]    [j + 1].rgbtGreen * Gx[1][2]
                   + image[i + 1][j + 1].rgbtGreen * Gx[2][2];

            y_comp = image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
        }

        if (component == 'r')
        {
            x_comp = image[i]    [j + 1].rgbtRed * Gx[1][2]
                   + image[i + 1][j + 1].rgbtRed * Gx[2][2];

            y_comp = image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];
        }         
    }

    // top right corner
    if (i == 0 && j == width - 1)
    {
        if (component == 'b')
        {
            x_comp = image[i]    [j - 1].rgbtBlue * Gx[1][0] 
                   + image[i + 1][j - 1].rgbtBlue * Gx[2][0];

            y_comp = image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1];
        }

        if (component == 'g')
        {
            x_comp = image[i]    [j - 1].rgbtGreen * Gx[1][0] 
                   + image[i + 1][j - 1].rgbtGreen * Gx[2][0];

            y_comp = image[i + 1][j - 1].rgbtGreen * Gy[2][0] + image[i + 1][j].rgbtGreen * Gy[2][1];
        }

        if (component == 'r')
        {
            x_comp = image[i]    [j - 1].rgbtRed * Gx[1][0] 
                   + image[i + 1][j - 1].rgbtRed * Gx[2][0];

            y_comp = image[i + 1][j - 1].rgbtRed * Gy[2][0] + image[i + 1][j].rgbtRed * Gy[2][1];
        }
    }

    // bottom left corner
    if (i == height - 1 && j == 0)
    {
        if (component == 'b')
        {
            x_comp =  image[i - 1][j + 1].rgbtBlue * Gx[0][2]
                    + image[i]    [j + 1].rgbtBlue * Gx[1][2];

            y_comp = image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2];
        }

        if (component == 'g')
        {
            x_comp =  image[i - 1][j + 1].rgbtGreen * Gx[0][2]
                    + image[i]    [j + 1].rgbtGreen * Gx[1][2];

            y_comp = image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2];
        }

        if (component == 'r')
        {
            x_comp =  image[i - 1][j + 1].rgbtRed * Gx[0][2]
                    + image[i]    [j + 1].rgbtRed * Gx[1][2];

            y_comp = image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2];
        }        
    }

    // bottom right corner
    if (i == height - 1 && j == width - 1)
    {
        if (component == 'b')
        {
            x_comp =    image[i - 1][j - 1].rgbtBlue * Gx[0][0]
                      + image[i]    [j - 1].rgbtBlue * Gx[1][0];

            y_comp =    image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1];
        }

        if (component == 'g')
        {
            x_comp =    image[i - 1][j - 1].rgbtGreen * Gx[0][0]
                      + image[i]    [j - 1].rgbtGreen * Gx[1][0];

            y_comp =    image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i - 1][j].rgbtGreen * Gy[0][1];
        }

        if (component == 'r')
        {
            x_comp =    image[i - 1][j - 1].rgbtRed * Gx[0][0]
                      + image[i]    [j - 1].rgbtRed * Gx[1][0];

            y_comp =    image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i - 1][j].rgbtRed * Gy[0][1];
        }
    }
     
    // top edge
    if (i == 0 && j > 0 && j < width - 1)
    {
        if (component == 'b')
        {
            x_comp = image[i]    [j - 1].rgbtBlue * Gx[1][0] + image[i]    [j + 1].rgbtBlue * Gx[1][2]
                   + image[i + 1][j - 1].rgbtBlue * Gx[2][0] + image[i + 1][j + 1].rgbtBlue * Gx[2][2];

            y_comp = image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
        }

        if (component == 'g')
        {
            x_comp = image[i]    [j - 1].rgbtGreen * Gx[1][0] + image[i]    [j + 1].rgbtGreen * Gx[1][2]
                   + image[i + 1][j - 1].rgbtGreen * Gx[2][0] + image[i + 1][j + 1].rgbtGreen * Gx[2][2];

            y_comp = image[i + 1][j - 1].rgbtGreen * Gy[2][0] + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
        }

        if (component == 'r')
        {
            x_comp = image[i]    [j - 1].rgbtRed * Gx[1][0] + image[i]    [j + 1].rgbtRed * Gx[1][2]
                   + image[i + 1][j - 1].rgbtRed * Gx[2][0] + image[i + 1][j + 1].rgbtRed * Gx[2][2];

            y_comp = image[i + 1][j - 1].rgbtRed * Gy[2][0] + image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];
        }
    }

    // bottom edge
    if (i == height - 1 && j > 0 && j < width - 1)
    {
        if (component == 'b')
        {
            x_comp =    image[i - 1][j - 1].rgbtBlue * Gx[0][0] + image[i - 1][j + 1].rgbtBlue * Gx[0][2]
                      + image[i]    [j - 1].rgbtBlue * Gx[1][0] + image[i]    [j + 1].rgbtBlue * Gx[1][2];

            y_comp =    image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2];
                      
        }

        if (component == 'g')
        {
            x_comp =    image[i - 1][j - 1].rgbtGreen * Gx[0][0] + image[i - 1][j + 1].rgbtGreen * Gx[0][2]
                      + image[i]    [j - 1].rgbtGreen * Gx[1][0] + image[i]    [j + 1].rgbtGreen * Gx[1][2];

            y_comp =    image[i - 1][j - 1].rgbtGreen * Gy[0][0] + image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2];
                      
        }

        if (component == 'r')
        {
            x_comp =    image[i - 1][j - 1].rgbtRed * Gx[0][0] + image[i - 1][j + 1].rgbtRed * Gx[0][2]
                      + image[i]    [j - 1].rgbtRed * Gx[1][0] + image[i]    [j + 1].rgbtRed * Gx[1][2];

            y_comp =    image[i - 1][j - 1].rgbtRed * Gy[0][0] + image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed00 * Gy[0][2];
                      
        }
    }

    // left edge
    if (i > 0 && i < height - 1 && j == 0)
    {
        if (component == 'b')
        {
            x_comp =  image[i - 1][j + 1].rgbtBlue * Gx[0][2]
                    + image[i]    [j + 1].rgbtBlue * Gx[1][2]
                    + image[i + 1][j + 1].rgbtBlue * Gx[2][2];

            y_comp =  image[i - 1][j].rgbtBlue * Gy[0][1] + image[i - 1][j + 1].rgbtBlue * Gy[0][2]
                    + image[i + 1][j].rgbtBlue * Gy[2][1] + image[i + 1][j + 1].rgbtBlue * Gy[2][2];
        }

        if (component == 'g')
        {
            x_comp =  image[i - 1][j + 1].rgbtGreen * Gx[0][2]
                    + image[i]    [j + 1].rgbtGreen * Gx[1][2]
                    + image[i + 1][j + 1].rgbtGreen * Gx[2][2];

            y_comp =  image[i - 1][j].rgbtGreen * Gy[0][1] + image[i - 1][j + 1].rgbtGreen * Gy[0][2]
                    + image[i + 1][j].rgbtGreen * Gy[2][1] + image[i + 1][j + 1].rgbtGreen * Gy[2][2];
        }

        if (component == 'r')
        {
            x_comp =  image[i - 1][j + 1].rgbtRed * Gx[0][2]
                    + image[i]    [j + 1].rgbtRed * Gx[1][2]
                    + image[i + 1][j + 1].rgbtRed * Gx[2][2];

            y_comp =  image[i - 1][j].rgbtRed * Gy[0][1] + image[i - 1][j + 1].rgbtRed * Gy[0][2]
                    + image[i + 1][j].rgbtRed * Gy[2][1] + image[i + 1][j + 1].rgbtRed * Gy[2][2];
        }
    }

    // right edge
    if (i > 0 && i < height - 1 && j == width - 1)
    {
        if (component == 'b')
        {
            x_comp =    image[i - 1][j - 1].rgbtBlue * Gx[0][0]
                      + image[i]    [j - 1].rgbtBlue * Gx[1][0]
                      + image[i + 1][j - 1].rgbtBlue * Gx[2][0];

            y_comp =    image[i - 1][j - 1].rgbtBlue * Gy[0][0] + image[i - 1][j].rgbtBlue * Gy[0][1]
                      + image[i + 1][j - 1].rgbtBlue * Gy[2][0] + image[i + 1][j].rgbtBlue * Gy[2][1];
        }
    }

    float result =  round(sqrt(x_comp * x_comp + y_comp * y_comp));

    if (result > 255)
    {
        result = 255;
    }

    return result;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // aux image
    RGBTRIPLE aux[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            aux[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // // center
            // if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            // {
            image[i][j].rgbtBlue = calc_sobel(i, j, 'b', height, width, aux);
            image[i][j].rgbtGreen = calc_sobel(i, j, 'g', height, width, aux);
            image[i][j].rgbtRed = calc_sobel(i, j, 'r', height, width, aux);
            // }
            
        }
    }
    
    
    
    
    return;
}
