#include <stdio.h>
#include <cs50.h>



int main(void)
{
    int height;
    int spacesNum;
    int hashesNum;

    do
    {
    height = get_int("How tall should the half-pyramid be? 0 <= height <= 23: ");
    }

    while (height < 0 || height > 23);

    for(int i = 1; i <= height; i++ )
    {
        for(spacesNum = 0; spacesNum < (height - i); spacesNum++)
            printf(" ");

        for(hashesNum = 0; hashesNum < i; hashesNum++)
            printf("#");

        printf("  ");

        for(hashesNum = 0; hashesNum < i; hashesNum++)
            printf("#");


        printf("\n");
    }
}