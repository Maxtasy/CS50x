// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // resize factor
    int n = atoi( argv[1]);
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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

    // create outfile headers from infile headers
    BITMAPFILEHEADER res_bf = bf;
    BITMAPINFOHEADER res_bi = bi;

    // edit width and height in header of outfile
    res_bi.biWidth = n * bi.biWidth;
    res_bi.biHeight = n * bi.biHeight;

    // determine infile's padding
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine outfile's padding
    int res_padding = (4 - (res_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate image size in bytes (# of RGBTRIPLE's + Padding bytes)
    res_bi.biSizeImage = abs(res_bi.biHeight) * res_bi.biWidth * sizeof(RGBTRIPLE) + res_padding * abs(res_bi.biHeight);

    // calculate outfile's complete file size (headers + image size)
    res_bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + res_bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&res_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&res_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines...
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        // ...n times (to expand on Y axis)
        for (int a = 0; a < n; a++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write each pixel n times into new file (to expand on X axis)
                for (int b = 0; b < n; b++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding to scanline of outfile
            for (int k = 0; k < res_padding; k++)
            {
                fputc(0x00, outptr);
            }
            // go back to beginning of current line of infile
            fseek(inptr, - (bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
        // skip forward to next scanline of infile
        fseek(inptr, bi.biWidth * sizeof(RGBTRIPLE) + padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
