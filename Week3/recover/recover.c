#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

FILE* addBufferToPicture(char* filename, int pictureNum, FILE* outptr, BYTE* buffer)
{
    sprintf(filename, "%03i.jpg", pictureNum);
    outptr = fopen(filename, "wb");
    fwrite(buffer, 512, 1, outptr);
    return outptr;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please give me one forensic image!\n");
        return 1;
    }

    FILE* inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open the card data.\n");
        return 2;
    }

    char filename[8];
    FILE* outptr = NULL;
    
    BYTE buffer[512];
    int pictureNum = 0;

    while (fread(buffer, 512, 1, inptr) == 1)
    {
        if (outptr == NULL)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                outptr = addBufferToPicture(filename, pictureNum, outptr, buffer);
            }
        }
        else if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(outptr);
            pictureNum += 1;
            outptr = addBufferToPicture(filename, pictureNum, outptr, buffer);
        }
        else
        {
            fwrite(buffer, 512, 1, outptr);
        }
    }

    fclose(outptr);
    fclose(inptr);
    return 0;
}