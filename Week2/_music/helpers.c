// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"
#include <math.h>

const int A4_FREQUENCY = 440;
const float NUM_SEMITONES_IN_OCTAVE = 12.0;

int getDistanceFromA(char letter);
float getSemiTone();
float getFrequenciesOfNoteA();

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
    const char letter = note[0];
    const char number = note[strlen(note) - 1];
    const int distance = getDistanceFromA(letter);
    float semiTone;

    if (strlen(note) == 3)
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

    const float freqA = getFrequenciesOfNoteA(number - '0');
    const float frequency = freqA * semiTone;

    return (int)round(frequency);
}

float getFrequenciesOfNoteA(int octave)
{
    const int octaveFromA4 = octave - 4;
    const float freq = (pow(2, octaveFromA4) * A4_FREQUENCY);
    return freq;
}

float getSemiTone(int distance)
{
    const float semiTone = pow(2, ((distance) / NUM_SEMITONES_IN_OCTAVE));
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
