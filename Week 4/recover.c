#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check correct usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    // Read 512 bites into a buffer
    BYTE buffer[512];

    // File* for recovered
    FILE *output = NULL;

    int count_file = 0;

    char *file = malloc(8 * sizeof(char));

    // Read buffer[512]
    while (fread(buffer, sizeof(char), 512, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Write names of files
            sprintf(file, "%03i.jpg", count_file);

            output = fopen(file, "w");

            count_file++;
        }
        if (output != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output);
        }
    }
    free(file);
    fclose(input);
    fclose(output);

    return 0;
}