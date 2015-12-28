/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize <n> <infile> <outfile>\n");
        return 1;
    }

    // remember filenames
    int resizeFactor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // only support 1 - 100
    if (resizeFactor < 1 || resizeFactor > 100)
    {
      printf("Only resizes between 1 and 100\n");
      return 1;
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // save the origional size
    int orgBiWidth = bi.biWidth;
    int orgBiHeight = bi.biHeight;

    // shift padding accordingly
    int padding = (4 - (orgBiWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int endPadding = (4 - ((bi.biWidth * sizeof(RGBTRIPLE)) % 4)) % 4;

    // resize bi height with new size
    bi.biWidth = bi.biWidth * resizeFactor;
    bi.biHeight = bi.biHeight * resizeFactor;

    // update with new image size information
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + endPadding) * abs(bi.biHeight);
    bf.bfSize = (bi.biSizeImage) + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, lines = abs(orgBiHeight); i < lines; i++)
    {
      // start seeking at start of scan line
      fpos_t currentScanLine;
      fgetpos(inptr, &currentScanLine);

        // iterate over pixels in scanline
        for (int j = 0; j < resizeFactor; j++)
        {
          if(j < resizeFactor)
          {
            fsetpos(inptr, &currentScanLine);
          }

          for(int k = 0; k < orgBiWidth; k++)
          {
              // temporary storage
              RGBTRIPLE triple;

              // read RGB triple from infile
              fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

              //write triple to new file
              for(int l = 0; l < resizeFactor; l++)
              {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
              }
          }
          //
          fseek(inptr, padding, SEEK_CUR);
          for(int m = 0; m < endPadding; m++)
          {
            fputc(0x00, outptr);
          }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
