/*
 * audio_signal.c
 * 
 * Copyright 2022  <fenix@raspberrypi>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>
 
#define N 160
 
int main(int argc, char **argv)
{
    int xn[N];
	float Xr[N];
	float Xi[N];
	int k = 0;
    //float real_square;
    //float imaginary_square;
    float magnitude;
    
    // Create a 20 ms audio buffer (assuming Fs = 8 kHz)
    int16_t buf[N] = {0}; // buffer
    int n;                // buffer index
     
    // Open WAV file with FFmpeg and read raw samples via the pipe.
    FILE *pipein;
    // pipein = popen("ffmpeg audio.wav -f s16le -ac 1 -", "r");
    pipein = popen("ffmpeg -i audio.wav -f s16le -ac 1 -", "r");
    fread(buf, 2, N, pipein);
    pclose(pipein);
     
    // Print the sample values in the buffer to a CSV file
    FILE *csvfile;
    csvfile = fopen("samples.csv", "w");
    for (n = 0; n < N; ++n) 
    fprintf(csvfile, "%d\n", buf[n]);
    fclose(csvfile);

    for (k = 0; k < N; k++) {
    Xr[k] = 0;
    Xi[k] = 0;
    for (n = 0; n < N; n++) {
        Xr[k] = (Xr[k] + xn[n] * cos(2 * 3.141592 * k * n / N));
        Xi[k] = (Xi[k] + xn[n] * sin(2 * 3.141592 * k * n / N));
    }
    
    /* Doing some few arithmetics here before saving magnitudes values */
    
    //real_square = Xr[k] * Xr[k];
    //imaginary_square = Xi[k] * Xi[k];
    magnitude = sqrt(Xr[k] * Xr[k] + Xi[k] * Xi[k]);
    
    // printing the magnitudes of the real and imaginary coefficients on a csv file
    
    FILE *csvfile;
    csvfile = fopen("magnitudes.csv", "w");
    fprintf(csvfile, "%f\n", magnitude);
    fclose(csvfile);

    printf("(%f) + j(%f)\n", Xr[k], Xi[k]);
    printf("(%f)\n", magnitude);
}
    
}
