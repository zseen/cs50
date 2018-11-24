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
    float distance = 0;

    if (letter == 'B')
    {
        distance += 2;
       
        
    }
    

    double semiTone;

    

  
    int frequency;

    for (int i = 0; i < number - 47; i++)
    {
        //printf("%d", i);
        if (noteLength == 3)
        {
          
            char modifier = note[strlen(note) - 2];
            
        
          
            if (modifier == '#')
            {   
                distance += 1;
                semiTone = pow(2, (distance / 12.0));
                frequency = getFrequenciesOfNoteA(i) * semiTone;               
            }
            else
            {
                int freqA = getFrequenciesOfNoteA(i);
               
                semiTone = pow(2, ((distance -1) / 12.0));

                printf("%f", semiTone);
                frequency = freqA * semiTone;
            }
        }
        else
        {
            semiTone = pow(2, (distance / 12.0));
            frequency = getFrequenciesOfNoteA(i) * semiTone;
        }
    }  
    return frequency;
}

int getFrequenciesOfNoteA(i)
{
    int frequency = round(pow(2, (i - 4)) * 440);
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
