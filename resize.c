/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, because David says so.
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
    if (atoi(argv[1]) > 100 || atoi(argv[1]) < 1)
    {
        printf("Please choose a positive integer from 1 to 100\n");
        return 1;
    }

    // remember filenames and factor
    int factor = atoi(argv[1]);
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
    
    // read infile's BITMAPFILEHEADER, create a copy
    BITMAPFILEHEADER bf_infile;
    fread(&bf_infile, sizeof(BITMAPFILEHEADER), 1, inptr);
    BITMAPFILEHEADER bf_outfile = bf_infile;

    // read infile's BITMAPINFOHEADER, create a copy
    BITMAPINFOHEADER bi_infile;
    fread(&bi_infile, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER bi_outfile = bi_infile;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf_infile.bfType != 0x4d42 || bf_infile.bfOffBits != 54 || bi_infile.biSize != 40 || 
        bi_infile.biBitCount != 24 || bi_infile.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // create temporary variables
    int bytesWide = bi_infile.biWidth * factor *  sizeof(RGBTRIPLE);
    int resizedPadding = (4 - (bytesWide % 4)) % 4;
    bi_outfile.biHeight = bi_infile.biHeight * factor;
    bi_outfile.biWidth = bi_infile.biWidth * factor;
    bi_outfile.biSizeImage = (bytesWide + resizedPadding) * abs(bi_outfile.biHeight);
    //bi_outfile.biSizeImage = (bi_infile.biWidth * abs(bi_outfile.biHeight) * sizeof(RGBTRIPLE)) + (resizedPadding * abs(bi_outfile.biHeight) * sizeof(resizedPadding));
    bf_outfile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_outfile.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_outfile, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_outfile, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // determine padding for scanlines
    int scan_padding =  (4 - (bi_infile.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi_infile.biHeight); i < biHeight; i++)
    {
        // vertical resize factoring
        for ( int j = 1; j <= factor; j++ )
        {
            // iterate over pixels in scanline
            for ( int k = 0; k < bi_infile.biWidth; k++ )
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for ( int l = 0; l < factor; l ++ )
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);   
                }  
            }
            
            // skip over padding, if any
            fseek(inptr, scan_padding, SEEK_CUR);
            
            // add padding for resized image
            for (int m = 0; m < resizedPadding; m++)
            {
                fputc(0x00, outptr);
            }
            
            if (j < factor)
            {
                fseek(inptr, -bi_infile.biWidth * sizeof(RGBTRIPLE) - scan_padding, SEEK_CUR);
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
