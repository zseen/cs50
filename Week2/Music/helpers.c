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
    

    int noteLength = strlen(note);
    char letter = note[0];
    char number;
    //printf("%c", letter);
    number = note[strlen(note) - 1];
    //printf("%c", number);
    int distance = 0;

    if (letter == 'B')
    {
        distance += 2;  
    }
    else if (letter == 'G')
    {
        distance -= 2;
    }
    else if (letter == 'F')
    {
        distance -= 4;
    }
    else if (letter == 'E')
    {
        distance -= 5;
    }
    else if (letter == 'D')
    {
        distance -= 7;
    }
    else if (letter == 'C')
    {
        distance -= 9;
    }
     
    float semiTone;
  
    float frequency;

    for (int i = 0; i < number - 47; i++)
    {
        if (noteLength == 3)
        {
            char modifier = note[strlen(note) - 2];
            float freqA = getFrequenciesOfNoteA(i);
 
            if (modifier == '#')
            {   
                //semiTone = getSemiTone(distance + 1);
                //printf("%f", semiTone);
                semiTone = pow(2, ((distance + 1) / 12.0));
                frequency = freqA * semiTone;               
            }
            else
            {     
                //semiTone = getSemiTone(distance - 1);
                semiTone = pow(2, ((distance - 1) / 12.0));
                //printf("%f", semiTone);
                frequency = freqA * semiTone;
            }
        }
        else
        {
            //semiTone = getSemiTone(distance);
            semiTone = pow(2, (distance / 12.0));
            printf("%f", semiTone);
            
            frequency = getFrequenciesOfNoteA(i) * semiTone;
        }
    }  
    return (int) round(frequency);
}

float getFrequenciesOfNoteA(i)
{
    float freq = (pow(2, (i - 4)) * 440);
    return freq;
}

float getSemiTone(distance)
{
    float semiTone = pow(2, (distance / 12.0));
    return semiTone;
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
