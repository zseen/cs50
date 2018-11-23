// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include <math.h>

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
    //printf("%s", note);
    int A4 = 440;
    int numSeminotes = 12;

    int noteLength = strlen(note);
    char letter = note[0];
    char number;
    //printf("%c", letter);
    number = note[strlen(note) - 1];
    //printf("%c", number);

    


    float frequency;

    for (int i = 0; i < number - 47; i++)
    {
        //printf("%d", i);
        if (noteLength == 3)
        {
          
            char modifier = note[strlen(note) - 2];
            double semiTone = pow(2, (1.0 / 12.0));
        
          
            if (modifier == '#')
            {
                
                frequency = round(pow(2, (i - 4)) * 440 * semiTone);
                
            }
            else
            {
                frequency = round(pow(2, (i - 4)) * 440 / semiTone);           
            }
        }
        else
        {
            frequency = round(pow(2, (i - 4)) * 440);           
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
