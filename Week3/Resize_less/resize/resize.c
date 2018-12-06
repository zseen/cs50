#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy size infile outfile\n");
        return 1;
    }

    int size = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (size < 1 || size > 100)
    {
        fprintf(stderr, "Size should be more than 1 and no more than 100");
        return 1;
    }

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    int inWidth = bi.biWidth;
    int inHeight = bi.biHeight;
    int inPadding = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biWidth *= size;
    bi.biHeight *= size;
    int outPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
  
    RGBTRIPLE* arrayRGBTRIPLE = (RGBTRIPLE*)malloc((bi.biWidth) * sizeof(RGBTRIPLE));

    for (int i = 0, biHeight = abs(inHeight); i < biHeight; i++)
    {
        for (int j = 0; j < inWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            arrayRGBTRIPLE[j] = triple;

            for (int m = 0; m < size; m++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        fseek(inptr, inPadding, SEEK_CUR);
        for (int o = 0; o < outPadding; o++)
        {
            fputc(0x00, outptr);
        }

        for (int a = 0; a < size - 1; ++a)
        {
            for (int b = 0; b < inWidth; ++b)
            {
                for (int c = 0; c < size; ++c)
                {
                    fwrite(&arrayRGBTRIPLE[b], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            for (int o = 0; o < outPadding; o++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    free(arrayRGBTRIPLE);

    fclose(inptr);
    fclose(outptr);

    return 0;
}
