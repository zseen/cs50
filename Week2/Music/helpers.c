// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include <math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numerator = fraction[0] - '0';
    int denominator = fraction[2] - '0';

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
    float frequency;
    float getSemiTone();
    float getFrequenciesOfNoteA();

    for (int i = 0; i < number - 47; i++)
    {
        float semiTone;
        float freqA = getFrequenciesOfNoteA(i);
        if (noteLength == 3)
        {
            char modifier = note[strlen(note) - 2];

            if (modifier == '#')
            {
                semiTone = getSemiTone(distance + 1);
            }
            else
            {
                semiTone = getSemiTone(distance - 1);
            }
        }
        else
        {
            semiTone = getSemiTone(distance);           
        }

        frequency = freqA * semiTone;
    }
    return  (int)round(frequency);
}

float getFrequenciesOfNoteA(int i)
{
    int A4frequency = 440;
    int standardStart = i - 4;
    float freq = (pow(2, standardStart) * A4frequency);
    return freq;
}

float getSemiTone(int distance)
{
    float numSemiTonesInOctave = 12.0;
    float semiTone = pow(2, ((distance) / numSemiTonesInOctave));
    return semiTone;
}

int getDistanceFromA(char letter)
{
    switch (letter)
    {
    case 'B':
        return 2;
    case 'G':
        return -2;
    case 'F':
        return -4;
    case 'E':
        return -5;
    case 'D':
        return -7;
    case 'C':
        return -9;
    default:
        return 0;
    }
    /*if (letter == 'B')
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
    return distance;*/
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
