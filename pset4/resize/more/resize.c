// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    float n = atof( argv[1]);
    if (n < 0.0 || n > 100.0)
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
    res_bi.biWidth = (int) round(n * bi.biWidth);
    res_bi.biHeight = (int) round(n * bi.biHeight);

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

    // read file into array (without padding).
    RGBTRIPLE inScanLines[abs(bi.biHeight)][bi.biWidth];

    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read RGB triple from infile
            fread(&(inScanLines[i][j]), sizeof(RGBTRIPLE), 1, inptr);
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // generate output file's scanline array, outScanLines
    RGBTRIPLE outScanLines[abs(res_bi.biHeight)][res_bi.biWidth];
    int indI;
    int indJ;

    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        indI = floor(i * n);
        for (int j = 0; j < bi.biWidth; j++)
        {
            indJ = ceil(n * j);
            outScanLines[indI][indJ] = inScanLines[i][j];
            for (int k = floor(n) - 1; k > 0; k--)
            {
                outScanLines[indI][indJ + k] = inScanLines[i][j];
            }
        }
        for (int l = floor(n) - 1; l > 0; l--)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                indJ = ceil(n*j);
                outScanLines[indI + l][indJ] = inScanLines[i][j];
                for (int k = floor(n) - 1; k > 0; k--)
                {
                    outScanLines[indI + l][indJ + k] = inScanLines[i][j];
                }
            }
        }
    }

    // write outScanLines array to output file with padding
    for (int i = 0; i < abs(res_bi.biHeight); i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < res_bi.biWidth; j++)
        {
            fwrite(&outScanLines[i][j], sizeof(RGBTRIPLE), 1, outptr);
        }

        // padding
        for (int k = 0; k < res_padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    // cleanup
    fclose(inptr);
    fclose(outptr);

    // success
    return 0;
}