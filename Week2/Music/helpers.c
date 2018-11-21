// Helper functions for music

#include <cs50.h>

#include "helpers.h"
#include<math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0];
    int denominator = fraction[1];
    int eightsNote = 8 / denominator * numerator;
    return eightsNote;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //printf("%c", note[strlen(note) - 1]);
    int A4 = 440;
    int numSeminotes = 12;



    //int A1 = pow(2, - 3 * 12 / 12) * 440; //pow(2, - (4 - 1) * 12 / 12) * 440;  pow(2, (Y - A4) * numSeminotes) * 440;
    //int A2 = pow(2, -2 * 12 / 12) * 440;
    int noteLength = strlen(note);
    char letter = note[0];
    char number;
    number = note[strlen(note) - 1];
    //printf("%c", number);
    int frequency;

    for (int i = 0; i < number - 48; i++)
    {
        {
            frequency = pow(2, ((i + 1 - 4) * numSeminotes / 12)) * 440;
        }

    }
    return frequency;
}


// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }
    return false;
}
