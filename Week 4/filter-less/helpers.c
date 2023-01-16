#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average value of the 3 colors
            double average = 0;

            average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            //round the value to the nearest integer
            average = round(average);

            // set every RGB value to average
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /* sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue*/

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the sepia colors
            double sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            double sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            double sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            //check if it is over 255
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


            // set every RGB value to sepia RGB
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //and one extra cup to keep the right colors
    double tmpRed = 0;
    double tmpGreen = 0;
    double tmpBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // swap the colors
            tmpRed = image[i][j].rgbtRed;
            tmpGreen = image[i][j].rgbtGreen;
            tmpBlue = image[i][j].rgbtBlue;

            //swap the left into the right
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            //left into temp
            image[i][width - 1 - j].rgbtRed = tmpRed;
            image[i][width - 1 - j].rgbtGreen = tmpGreen;
            image[i][width - 1 - j].rgbtBlue = tmpBlue;


        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // decalre variables to store data
    int invalid = 0;
    double avrgRed = 0;
    double avrgGreen = 0;
    double avrgBlue = 0;

    //try to simulate every movement and check if is outside
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            //  make this stuff "\" up
            i -= 1;
            j -= 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i += 1;
                j += 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i += 1;
                j += 1;

            }

            //  make this stuff "|" up
            i -= 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i += 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i += 1;

            }

            //  make this stuff "/" up
            i -= 1;
            j += 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i += 1;
                j -= 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i += 1;
                j -= 1;

            }

            // make this stuff "-" right
            j += 1 ;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                j -= 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                j -= 1;

            }

            // make this stuff "\" down
            i += 1;
            j += 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i -= 1;
                j -= 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i -= 1;
                j -= 1;

            }

            // make this stuff "|" down

            i += 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i -= 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i -= 1;
            }

            // make this stuff "/" down
            i += 1;
            j -= 1;

            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                i -= 1;
                j += 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                i -= 1;
                j += 1;

            }

            // make this stuff left "-"
            j -= 1;


            if (i < 0 || j < 0 || i > (height - 1) || j > (width - 1))
            {
                invalid += 1;
                j += 1;
            }
            else
            {
                avrgRed += image[i][j].rgbtRed;
                avrgGreen += image[i][j].rgbtGreen;
                avrgBlue += image[i][j].rgbtBlue;
                j += 1;

            }

            avrgRed = round(avrgRed / (9.0 - invalid));
            avrgGreen = round(avrgGreen / (9.0 - invalid));
            avrgBlue = round(avrgBlue / (9.0 - invalid));

            image[i][j].rgbtRed = round(avrgRed);
            image[i][j].rgbtGreen = round(avrgGreen);
            image[i][j].rgbtBlue = round(avrgBlue);

            avrgRed = 0;
            avrgGreen = 0;
            avrgBlue = 0;
            invalid = 0;

            // fail miserably
        }
    }
    return;
}
