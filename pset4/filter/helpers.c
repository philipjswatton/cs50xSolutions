#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            double newColour = (double) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            image[i][j].rgbtRed = (int) round(newColour);
            image[i][j].rgbtGreen = (int) round(newColour);
            image[i][j].rgbtBlue = (int) round(newColour);
        }
    }
}

// Convert image to sepia
  /* Formula to use for sepia:
  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

  Make sure to max out at 255*/
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            double newRed = (double) .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            double newGreen = (double) .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            double newBlue = (double) .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if (newRed <= 255) {
                image[i][j].rgbtRed = (int) round(newRed);
            } else {
                image[i][j].rgbtRed = 255;
            }

            if (newGreen <= 255) {
                image[i][j].rgbtGreen = (int) round(newGreen);
            } else {
                image[i][j].rgbtGreen = 255;
            }

            if (newBlue <= 255) {
                image[i][j].rgbtBlue = (int) round(newBlue);
            } else {
                image[i][j].rgbtBlue = 255;
            }
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    //allocate memory to temporarily store values to switch
    RGBTRIPLE* temp = malloc(width * sizeof(RGBTRIPLE));

    //loop over image
    for (int i = 0; i < height; i++) {

        //store values in temporary array of ints
        for  (int j = 0; j < width; j++) {
            temp[j].rgbtRed = image[i][j].rgbtRed;
            temp[j].rgbtGreen = image[i][j].rgbtGreen;
            temp[j].rgbtBlue = image[i][j].rgbtBlue;
        }

        //move values from temp array to new locations in image

        int countReverse = width - 1; //we need to count in reverse
        for (int j = 0; j < width; j++) {
            image[i][j].rgbtRed = temp[countReverse].rgbtRed;
            image[i][j].rgbtGreen = temp[countReverse].rgbtGreen;
            image[i][j].rgbtBlue = temp[countReverse].rgbtBlue;

            countReverse--;
        }
    }

    // free memory allocated to temporary array
    free(temp);

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //allocate memory to temporary image to calculate new values from
    RGBTRIPLE temp[height][width];

    //store image in temp file
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //loop over image, calulating new values conditional on whether or not the pixel is on an edge/in a corner. In each case, delte 'impossible values', e.g. i-1 where i is 0
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 && j == 0) { //top left

                //red
                double newRed = (double) (temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/4);

                //green
                double newGreen = (double) (temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/4);

                //blue
                double newBlue = (double) (temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/4);

            } else if (i == 0 && j == width - 1) { //top right

                //red
                double newRed = (double) (temp[i+1][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i][j-1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/4);

                //green
                double newGreen = (double) (temp[i+1][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/4);

                //blue
                double newBlue = (double) (temp[i+1][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/4);

            } else if (i == 0) { //top row

                //red
                double newRed = (double) (temp[i+1][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/6);

                //green
                double newGreen = (double) (temp[i+1][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen)/6;

                //blue
                double newBlue = (double) (temp[i+1][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/6);

            } else if (i == height - 1 && j == 0) { //bottom left

                //red
                double newRed = (double) (temp[i][j+1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/4);

                //green
                double newGreen = (double) (temp[i][j+1].rgbtGreen +temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/4) ;

                //blue
                double newBlue = (double) (temp[i][j+1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/4);

            } else if (i == height - 1 && j == width - 1) { //bottom right

                //red
                double newRed = (double) (temp[i][j-1].rgbtRed + temp[i-1][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/4);

                //green
                double newGreen = (double) (temp[i][j-1].rgbtGreen + temp[i-1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/4);

                //blue
                double newBlue = (double) (temp[i][j-1].rgbtBlue + temp[i-1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/4);

            } else if (i == height - 1) { //bottom row

                //red
                double newRed = (double) (temp[i-1][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/6);

                //green
                double newGreen = (double) (temp[i-1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/6);

                //blue
                double newBlue = (double) (temp[i-1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/6);

            } else if (j == 0) { //left column

                //red
                double newRed = (double) (temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j+1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/6);

                //green
                double newGreen = (double) (temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/6);

                //blue
                double newBlue = (double) (temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/6);

            } else if (j == width - 1) { //right column

                //red
                double newRed = (double) (temp[i+1][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i][j-1].rgbtRed + temp[i-1][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/6);

                //green
                double newGreen = (double) (temp[i+1][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i-1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/6);

                //blue
                double newBlue = (double) (temp[i+1][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i-1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/6);

            } else { //the rest

                //red
                double newRed = (double) (temp[i+1][j-1].rgbtRed + temp[i+1][j].rgbtRed + temp[i+1][j+1].rgbtRed + temp[i][j-1].rgbtRed + temp[i][j+1].rgbtRed + temp[i-1][j-1].rgbtRed + temp[i-1][j].rgbtRed + temp[i-1][j+1].rgbtRed + temp[i][j].rgbtRed);
                image[i][j].rgbtRed = (int) round(newRed/9);

                //green
                double newGreen = (double) (temp[i+1][j-1].rgbtGreen + temp[i+1][j].rgbtGreen + temp[i+1][j+1].rgbtGreen + temp[i][j-1].rgbtGreen + temp[i][j+1].rgbtGreen + temp[i-1][j-1].rgbtGreen + temp[i-1][j].rgbtGreen + temp[i-1][j+1].rgbtGreen + temp[i][j].rgbtGreen);
                image[i][j].rgbtGreen = (int) round(newGreen/9);

                //blue
                double newBlue = (double) (temp[i+1][j-1].rgbtBlue + temp[i+1][j].rgbtBlue + temp[i+1][j+1].rgbtBlue + temp[i][j-1].rgbtBlue + temp[i][j+1].rgbtBlue + temp[i-1][j-1].rgbtBlue + temp[i-1][j].rgbtBlue + temp[i-1][j+1].rgbtBlue + temp[i][j].rgbtBlue);
                image[i][j].rgbtBlue = (int) round(newBlue/9);
            }
        }
    }
}
