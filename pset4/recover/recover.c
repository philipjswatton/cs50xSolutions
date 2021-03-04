#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;
FILE* output;

int main(int argc, char *argv[])
{
    // Ensure correct number of arguments
    if (argc != 2) {
        printf("Correct usage: recover filename\n");
        return 1;
    }

    // Open the file
    FILE* card = fopen(argv[1], "r");

    // Ensure the file can be opened/exists
    if (card == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    /*The implication of all these details is that you, the investigator, can probably write a program that iterates over a copy of my memory card,
    looking for JPEGs’ signatures. Each time you find a signature, you can open a new file for writing and start filling that file with bytes
    from my memory card, closing that file only once you encounter another signature. Moreover, rather than read my memory card’s bytes one at a
    time, you can read 512 of them at a time into a buffer for efficiency’s sake. Thanks to FAT, you can trust that JPEGs’ signatures will be
    “block-aligned.” That is, you need only look for those signatures in a block’s first four bytes.*/

    // Initialise a buffer
    BYTE buffer[BLOCK_SIZE];

    // Create a file counter
    int count = 0;

    // Initialise a file name
    char name[8]; //3 for digits, 4 for ".jpg", 1 for null character

    // Read into buffer 512 bytes, check contents, write into files as appropriate
    while (fread(buffer, 1, BLOCK_SIZE, card)) {

        //Check first four bytes for JPEG file start
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xee) {

            // close old file if count already > 1
            if (count > 1) {
                fclose(output);
            }

            // if encounter the first four bytes, start writing a new file and increment the counter
            snprintf(name, 8, "%03i.jpg", count);
            count++;

            // open new file, write to file
            output = fopen(name, "w");
            fwrite(buffer, 1, BLOCK_SIZE, output);

        } else {

            //if counter > 0, write to current file, else do nothing
            if (count > 0) {

                // write to file
                fwrite(buffer, 1, BLOCK_SIZE, output);

            }
        }
    }

    // Close the file
    fclose(card);
}