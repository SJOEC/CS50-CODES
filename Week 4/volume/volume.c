// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    // Create a variable to store the readed data
    uint8_t header[HEADER_SIZE];

    // copy the data into the "header" variable from the input
    fread(header, HEADER_SIZE, 1, input);

    // copy the readed data into the output file
    fwrite(header, HEADER_SIZE, 1, output);

    // Create a variable to store the samples
    int16_t buffer;

    while (fread(&buffer, 2, 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, 2, 1, output);

    }
    // Close files
    fclose(input);
    fclose(output);
}
