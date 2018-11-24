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
    int noteLength = strlen(note);
    char letter = note[0];
    char number = note[strlen(note) - 1];

    int getDistanceFromA();
    int distance = getDistanceFromA(letter);

    float getSemiTone();
    float getFrequenciesOfNoteA();
    float semiTone;
    float frequency;

    for (int i = 0; i < number - 47; i++)
    {
        float freqA = getFrequenciesOfNoteA(i);
        if (noteLength == 3)
        {
            char modifier = note[strlen(note) - 2];

            if (modifier == '#')
            {
                semiTone = getSemiTone(distance + 1);
                frequency = freqA * semiTone;
            }
            else
            {
                semiTone = getSemiTone(distance - 1);
                frequency = freqA * semiTone;
            }
        }
        else
        {
            printf("%d", distance);
            semiTone = getSemiTone(distance);
            frequency = freqA * semiTone;
        }
    }
    return  (int)round(frequency);
}

float getFrequenciesOfNoteA(i)
{
    float freq = (pow(2, (i - 4)) * 440);
    return freq;
}

float getSemiTone(distance)
{
    float semiTone = pow(2, ((distance) / 12.0));
    return semiTone;
}

int getDistanceFromA(letter)
{
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
    return distance;
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
