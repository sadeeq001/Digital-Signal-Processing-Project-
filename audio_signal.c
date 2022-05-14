/*
 * audio_signal.c
 * 
 * Copyright 2022  <fenix@raspberrypi>
 * 
 * This program is free software; you can sinredistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * sin
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
#include <time.h>  // for clock_t, clock(), CLOCKS_PER_SEC
 
#define N 10000 // audio duration = 12:08 minutes, hence N = 244 X 8000KHz = 1952000
 
int main(int argc, char **argv)
{
    // to store the execution time of code
    double time_spent = 0.0;
 
    
    
    //int xn[N];
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
    pipein = popen("ffmpeg -i sample_audio.wav -f s16le -ac 1 -", "r");
    fread(buf, 2, N, pipein);
    pclose(pipein);
     
    // Print the sample values in the buffer to a CSV file
    FILE *csvfile;
    csvfile = fopen("samples.csv", "w");
    for (n = 0; n < N; ++n) 
    fprintf(csvfile, "%d\n", buf[n]);
    fclose(csvfile);
    
    clock_t begin = clock();
    
    for (k = 0; k < N; k++) {
    Xr[k] = 0;
    Xi[k] = 0;
    for (n = 0; n < N; n++) {
    Xr[k] = (Xr[k] + buf[n] * cos(2 * 3.141592 * k * n / N));
    Xi[k] = (Xi[k] + buf[n] * sin(2 * 3.141592 * k * n / N));
    }
    
    /* Doing some few arithmetics here before saving magnitudes values */
    
    //real_square = Xr[k] * Xr[k];
    //imaginary_square = Xi[k] * Xi[k];
    magnitude = sqrt(Xr[k] * Xr[k] + Xi[k] * Xi[k]);
    
}

    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds", time_spent);
    

    for (k = 0; k < N; k++) {
    Xr[k] = 0;
    Xi[k] = 0;
    for (n = 0; n < N; n++) {
    Xr[k] = (Xr[k] + buf[n] * cos(2 * 3.141592 * k * n / N));
    Xi[k] = (Xi[k] + buf[n] * sin(2 * 3.141592 * k * n / N));
    }
    
    /* Doing some few arithmetics here before saving magnitudes values */
    
    //real_square = Xr[k] * Xr[k];
    //imaginary_square = Xi[k] * Xi[k];
    magnitude = sqrt(Xr[k] * Xr[k] + Xi[k] * Xi[k]);
    
    // printing the magnitudes of the real and imaginary coefficients on a csv file
    
    FILE *magnitudefile;
    magnitudefile = fopen("magnitudes.csv", "a");
    fprintf(magnitudefile, "%f\n", magnitude);
    fclose(magnitudefile);
    
}

    //printf("(%f) + j(%f)\n", Xr[k], Xi[k]);
    //printf("(%f)\n", magnitude);
    
}
