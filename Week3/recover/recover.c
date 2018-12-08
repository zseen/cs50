#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>



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

    fread(buffer, 512, 1, inptr);
    char filename[8];
    sprintf(filename, "%03i.jpg", numberthPicture);
    FILE* img = fopen(filename, "w"); //filename = char array to store the result string

    fwrite(buffer, 512, 1, outfile); //FILE* to write to

   int x = fread(buffer, 512, 1, inptr); // x should be equal to number, so 1, it should be a condition!!!





   
}