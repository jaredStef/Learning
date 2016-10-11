/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    FILE* o_file;

    BYTE readBuffer[512];

    int imgNum = 0;

    while (!feof(file))
    {
        fread(readBuffer, sizeof(readBuffer), 1, file);

        if (readBuffer[0] == 0xff && readBuffer[1] == 0xd8 && readBuffer[2] == 0xff && readBuffer[3] >= 0xe0 && readBuffer[3] <= 0xef)
        {
            char fileName[8];
            sprintf(fileName, "%03i.jpg", imgNum);
            o_file = fopen(fileName, "w");
            fwrite(readBuffer, sizeof(readBuffer), 1, o_file);
            imgNum += 1;
        }
        else if (imgNum > 0)
        {
            // it is not the header of the image, so continue writing
            fwrite(readBuffer, sizeof(readBuffer), 1, o_file);
        }
    }

    fclose(file);
    fclose(o_file);

    return 0;
}
