// Helper functions for music
#include <string.h>
#include <cs50.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int nom = fraction[0] - '0';
    int denom = fraction[2] - '0';
    int num = 8 / denom;
    return nom * num;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter[strlen(note) + 1];
    for (int i = 0; i < strlen(note) - 1; i++)
    {
        letter[i] = note[i];
    }
    letter[strlen(note) - 1] = '\0';

    int oct = note[strlen(note) - 1] - '0';

    int dist = 0;

    if (strcmp(letter, "C") == 0)
    {
        dist = -9;
    }
    else if (strcmp(letter, "C#") == 0 || strcmp(letter, "Db") == 0)
    {
        dist = -8;
    }
    else if (strcmp(letter, "D") == 0)
    {
        dist = -7;
    }
    else if (strcmp(letter, "D#") == 0 || strcmp(letter, "Eb") == 0)
    {
        dist = -6;
    }
    else if (strcmp(letter, "E") == 0)
    {
        dist = -5;
    }
    else if (strcmp(letter, "F") == 0)
    {
        dist = -4;
    }
    else if (strcmp(letter, "F#") == 0 || strcmp(letter, "Gb") == 0)
    {
        dist = -3;
    }
    else if (strcmp(letter, "G") == 0)
    {
        dist = -2;
    }
    else if (strcmp(letter, "G#") == 0 || strcmp(letter, "Ab") == 0)
    {
        dist = -1;
    }
    else if (strcmp(letter, "A") == 0)
    {
        dist = 0;
    }
    else if (strcmp(letter, "A#") == 0 || strcmp(letter, "Bb") == 0)
    {
        dist = 1;
    }
    else if (strcmp(letter, "B") == 0)
    {
        dist = 2;
    }

    int total_dist = (oct - 4) * 12 + dist;

    return round(pow(2, (float) total_dist / (float) 12) * 440);
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
