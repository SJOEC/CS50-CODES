#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE; // create a variable called "BYTE", that store 1 byte
    BYTE buffer[512]; // 512 bytes buffer
    int jpg_counter = 0; // Image counter
    char *filename = malloc(8); // array to store the name of the output files
    FILE *output = NULL; 

    // check user input
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        free(filename);
        return 1;
    }

    // open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open the card.\n");
        return 1;
    }

    // look for begining of a JPEG file until the end of the file
    while (fread(buffer, 1, 512, card) == 512)
    {
        // found a jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // if a file is already open, close it
            if (jpg_counter == 0)
            {
                //create the name of the file
                sprintf(filename, "%03i.jpg", jpg_counter);

                //open a new file to write into
                output = fopen(filename, "w");

                //write into the new file
                fwrite(buffer, 1, 512, output);
                jpg_counter += 1;
            }
            else
            {
                fclose(output);

                sprintf(filename, "%03i.jpg", jpg_counter);

                //open a new file to write into
                output = fopen(filename, "w");

                //write into the new file
                fwrite(buffer, 1, 512, output);
                jpg_counter += 1;

            }
        }
        // if isnt a header of a new file, keep write into
        else if (jpg_counter > 0)
        {
            fwrite(buffer, 1, 512, output);
        }
    }

    // close the files
    fclose(output);
    fclose(card);

    // free memory with maloc
    free(filename);
}