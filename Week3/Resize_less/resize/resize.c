#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


void writePadding(int outPadding, FILE* outptr)
{
    for (int paddingNeeded = 0; paddingNeeded < outPadding; paddingNeeded++)
    {
        fputc(0x00, outptr);
    }
}

void writeLineVertically(int imageResizeFactor, int inWidth, RGBTRIPLE* arrayRGBTRIPLE, int size, FILE* outptr, int outPadding)
{
    for (int pixelPosition = 0; pixelPosition < inWidth; ++pixelPosition)
    {
        for (int lineLength = 0; lineLength < imageResizeFactor; ++lineLength)
        {
            fwrite(&arrayRGBTRIPLE[pixelPosition], size, 1, outptr);
        }
    }

    writePadding(outPadding, outptr);  
}

RGBTRIPLE* putPixelInEnlargedLine(int imageResizeFactor, int inWidth, FILE* inptr)
{
    RGBTRIPLE* arrayRGBTRIPLE = (RGBTRIPLE*)malloc((inWidth * imageResizeFactor) * sizeof(RGBTRIPLE));

    for (int j = 0; j < inWidth; j++)
    {
        RGBTRIPLE triple;
        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
        arrayRGBTRIPLE[j] = triple; 
    }
   
    return arrayRGBTRIPLE;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy size infile outfile\n");
        return 1;
    }

    int imageResizeFactor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (imageResizeFactor < 1 || imageResizeFactor > 100)
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

    bi.biWidth *= imageResizeFactor;
    bi.biHeight *= imageResizeFactor;
    int outPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    for (int i = 0, biHeight = abs(inHeight); i < biHeight; i++)
    {
        RGBTRIPLE* pixelsArray = putPixelInEnlargedLine(imageResizeFactor, inWidth, inptr);
        printf("%lu\n", sizeof(pixelsArray));
        
        fseek(inptr, inPadding, SEEK_CUR);
        writePadding(outPadding, outptr);

        for (int repeat = 0; repeat < imageResizeFactor; ++repeat)
        {
            writeLineVertically(imageResizeFactor, inWidth, pixelsArray, sizeof(RGBTRIPLE), outptr, outPadding);
        }
    }

    //free(arrayRGBTRIPLE);

    fclose(inptr);
    fclose(outptr);

    return 0;
}


