#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./copy clue verdict\n");
        return 1;
    }

    // remember filenames
    char* clue = argv[1];
    char* verdict = argv[2];

    // open input file 
    FILE* inptr = fopen(clue, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", clue);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(verdict, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", verdict);
        return 3;
    }

    // read clue's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read clue's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure clue is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write verdict's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write verdict's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over clue's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from clue
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            if ( triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00 && triple.rgbtRed == 0xff )
            {
                triple.rgbtBlue = 0xff, triple.rgbtGreen = 0xff, triple.rgbtRed = 0xff;
            }
            if ( triple.rgbtBlue == 0xcf && triple.rgbtGreen == 0xe9 && triple.rgbtRed == 0xe9 ) 
            {
                triple.rgbtBlue = 0x00, triple.rgbtGreen = 0xff, triple.rgbtRed = 0x00;
            }

            // write RGB triple to verdict
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close clue
    fclose(inptr);

    // close verdict
    fclose(outptr);

    // that's all folks
    return 0;
}
