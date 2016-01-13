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

int main(void)
{
  FILE* file = fopen("card.raw", "r");
  FILE* outputFile = NULL;

  int fileCounter = 0;
  BYTE readBuffer[512];

  while (!feof(file))
  {
    fread(readBuffer, sizeof(readBuffer), 1, file);
    if(readBuffer[0] == 0xff && readBuffer[1] == 0xd8 && readBuffer[2] == 0xff && (readBuffer[3] == 0xe0 || readBuffer[3] == 0xe1) )
    {
      fileCounter++;
      // 7 bytes 2 digit number, 4 .jpg, and null terminator
      char fileName[7];
      sprintf(fileName, "%d.jpg", fileCounter);
      printf("%s recovered!!\n", fileName);
      outputFile = fopen(fileName,"w");
      fwrite(readBuffer, sizeof(readBuffer), 1, outputFile);
    }
    else if (fileCounter > 0)
    {
      // if it is not a jpeg and my counter is in one write it out
      fwrite(readBuffer, sizeof(readBuffer), 1, outputFile);
    }
  }
  fclose(file);
  fclose(outputFile);
  return 0;
}
