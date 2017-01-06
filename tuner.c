/*
This example program makes use of the simple
sound library to generate a sine wave and write the
output to sound.wav.
For complete documentation on the library, see:
http://www.nd.edu/~dthain/courses/cse20211/fall2013/wavfile
Go ahead and modify this program for your own purposes.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "wavfile.h"

const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND * 2) / 4;

int main()
{
    short waveform[NUM_SAMPLES];
    int volume = 32000;
    int length = NUM_SAMPLES;
    double freqs [6];

    FILE *f = wavfile_open("tunes.wav");
    if (!f)
    {
        printf("couldn't open tunes.wav for writing: %s", strerror(errno));
        return -1;
    }

    FILE* notes = fopen ("notes", "r");
    if (notes != NULL)
    {
        char buffer [16];
        int i = 0;
        while (fgets (buffer, 16, notes) != NULL)
        {
            buffer[strlen (buffer) - 1] = 0;
            char * freq_str = strstr (buffer, ",");
            freq_str++;

            freqs[i] = atof (freq_str);
            printf ("Freq: %f\n", freqs[i]);
            i++;
        }

        fclose (notes);
    }

    for (int j = 0; j < 6; j++)
    {
        double frequency = freqs[j];
        for (int i = 0; i < length; i++)
        {
            double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;
            waveform[i] = volume * sin(frequency * t * 2 * M_PI);
        }
        wavfile_write(f, waveform, length);
    }
    wavfile_close(f);

    return 0;
}
