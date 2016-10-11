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
        printf("Usage: ./resize factor infile outfile\n");
        return 1;
    }

    int scaleFactor = atoi(argv[1]);

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

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

    if (scaleFactor <= 0 && scaleFactor > 100)
    {
        printf("Scale factor must be between 1 and 100");
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER og_bf;
    fread(&og_bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER og_bi;
    fread(&og_bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (og_bf.bfType != 0x4d42 || og_bf.bfOffBits != 54 || og_bi.biSize != 40 ||
        og_bi.biBitCount != 24 || og_bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int og_padding =  (4 - (og_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate new header information and padding size

    BITMAPFILEHEADER n_bf = og_bf;

    BITMAPINFOHEADER n_bi = og_bi;

    n_bi.biWidth  *= scaleFactor;
    n_bi.biHeight *= scaleFactor;

    int n_padding = (4 - (n_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    n_bi.biSizeImage = n_bi.biWidth * abs(n_bi.biHeight) * sizeof(RGBTRIPLE) + (n_padding * abs(n_bi.biHeight));
    n_bf.bfSize = n_bi.biSizeImage + sizeof(n_bf) + sizeof(n_bi);

    // write outfile's BITMAPFILEHEADER
    fwrite(&n_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&n_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE linePixels[abs(og_bi.biHeight)][(int)og_bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(og_bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < og_bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // add pixels to array
            linePixels[i][j] = triple;
        }

        fseek(inptr, og_padding, SEEK_CUR);
    }

    // go to beginning of out file past the header information
    fseek(outptr, n_padding, SEEK_SET);
    fseek(outptr, sizeof(n_bi) + sizeof(n_bf),SEEK_CUR);

    for(int line = 0; line < abs(og_bi.biHeight); line++)
    {
        for (int zz = 0; zz < scaleFactor; zz++)
        {
            for (int item = 0; item < og_bi.biWidth; item++)
            {
                for(int k = 0; k < scaleFactor; k++)
                {
                    fwrite(&linePixels[line][item], sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // seek past padding at end of each row
            fseek(outptr, n_padding, SEEK_CUR);
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
