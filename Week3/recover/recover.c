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

}