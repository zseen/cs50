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
    int octaveFromA4 = i - 4;
    float freq = (pow(2, octaveFromA4) * A4frequency);
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
    int distance;
    switch (letter)
    {
        case 'B':
            distance = 2;
            break;
        case 'G':
            distance = -2;
            break;
        case 'F':
            distance = -4;
            break;
        case 'E':
            distance = -5;
            break;
        case 'D':
            distance = -7;
            break;
        case 'C':
            distance = -9;
            break;
        default:
            distance = 0;
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
