#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height = -1;

    while (height < 0 || height > 23)
    {
        height = get_int("How tall should the half-pyramid be? 0 <= height <= 23: ");
    }

    for (int i = 2; i <= height + 1; i++)
    {
        for (int spacesNum = 0; spacesNum < (height - i + 1); spacesNum++)
        {
            printf(" ");
        }

        for (int hashesNum = 0; hashesNum < i; hashesNum++)
        {
            printf("#");
        }

        printf("\n");
    }
}