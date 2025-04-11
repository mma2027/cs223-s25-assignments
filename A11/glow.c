#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
    // todo: your code here
    // compute image
    int w;
    int h;
    struct ppm_pixel** pixels = read_ppm_2d("earth-small.ppm", &w, &h);
    
    //failsafe
    if (pixels == NULL) {
        printf("Error: Failed to read the image\n");
        return 1;  // Indicate error state
    }

    struct ppm_pixel** blur = malloc(h * sizeof(struct ppm_pixel*));
    for (int i = 0; i < h; i++){
        blur[i] = malloc(w * sizeof(struct ppm_pixel));
        //checking if there is enough space
        if (!blur[i]) {
            //freeing the rest
            for (int j = 0; j < i; j++) {
                free(blur[j]);
            }
            free(blur);
        }
    }

    struct ppm_pixel** bright = malloc(h * sizeof(struct ppm_pixel*));
    for (int i = 0; i < h; i++){
        bright[i] = malloc(w * sizeof(struct ppm_pixel));
        //checking if there is enough space
        if (!bright[i]) {
            //freeing the rest
            for (int j = 0; j < i; j++) {
                free(bright[j]);
            }
            free(bright);
        }
    }

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            if (pixels[y][x].red + pixels[y][x].green + pixels[y][x].blue > 600){
                bright[y][x].red = pixels[y][x].red;
                bright[y][x].green = pixels[y][x].green;
                bright[y][x].blue = pixels[y][x].blue;
            } else {
                bright[y][x].red = 0;
                bright[y][x].green = 0;
                bright[y][x].blue = 0;
            }
        }
    }

    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            int startX = x - 12;
            int endX = x + 13;
            int startY = y - 12;
            int endY = y + 13;

            if (startX < 0) startX = 0;
            if (endX > w) endX = w;
            if (startY < 0) startY = 0;
            if (endY > h) endY = h;

            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;
            for( int i = startY; i < endY; i++ ){
                for ( int j = startX; j < endX; j++ ){
                    sumR += bright[i][j].red;
                    sumG += bright[i][j].green;
                    sumB += bright[i][j].blue;
                    count++;
                }
            }
            blur[y][x].red = sumR / count;
            blur[y][x].green = sumG / count;
            blur[y][x].blue = sumB / count;
        }
    }

    
    for (int y = 0; y < h; y++){
        for (int x = 0; x < w; x++){
            if (pixels[y][x].red + blur[y][x].red > 255) {
                pixels[y][x].red = 255;
            } else {
                pixels[y][x].red += blur[y][x].red;
            }

            if (pixels[y][x].blue + blur[y][x].blue > 255) {
                pixels[y][x].blue = 255;
            } else {
                pixels[y][x].blue += blur[y][x].blue;
            }

            if (pixels[y][x].green + blur[y][x].green > 255) {
                pixels[y][x].green = 255;
            } else {
                pixels[y][x].green += blur[y][x].green;
            }

        }
    }
    
    write_ppm_2d("glow.ppm", pixels, w, h);

    //free malloc
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
        free(blur[i]);
        free(bright[i]);
    }
    free(pixels);
    free(blur);
    free(bright);
}
