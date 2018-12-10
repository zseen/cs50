#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


typedef uint8_t BYTE;

bool isItJPEGStart(BYTE* bytes)
{
    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}

void nameJPEGFile(char* filename, int fileNum)
{
    sprintf(filename, "%03i.jpg", fileNum);  
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
    int bufferSize = 512;
    int pictureNum = 0;

    while (fread(buffer, bufferSize, 1, inptr) == 1)
    {
        if (isItJPEGStart(buffer))
        {
            if (outptr != NULL)
            {
                fclose(outptr);  
            }
            nameJPEGFile(filename, pictureNum);
            outptr = fopen(filename, "wb");
            fwrite(buffer, bufferSize, 1, outptr);
            pictureNum += 1;
        }
        else
        {
            if (outptr != NULL)
            {
                fwrite(buffer, bufferSize, 1, outptr);
            }           
        }
    }

    fclose(outptr);
    fclose(inptr);
    return 0;
}