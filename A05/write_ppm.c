/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Writes a binary file from an array.
 ---------------------------------------------*/
#include "write_ppm.h"
#include <stdio.h>
#include <string.h>

// implement *one* (but do not remove the other one)!

void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {

}

void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
    // Open the file in binary write mode and return NULL if it can't be opened
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        return;
    }

    //header information
    fprintf(fp, "P6\n");
    fprintf(fp, "#\n"); 
    fprintf(fp, "%d %d\n", w, h);  
    fprintf(fp, "255\n");           

    // Write the pixel data
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // Write the RGB values for each pixel
            fwrite(&pixels[i][j].red, sizeof(unsigned char), 1, fp);
            fwrite(&pixels[i][j].green, sizeof(unsigned char), 1, fp);
            fwrite(&pixels[i][j].blue, sizeof(unsigned char), 1, fp);
        }
    }

    fclose(fp);  // Close the file
}