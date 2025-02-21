/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Program that glitches an image file
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char** argv) {
    //image file name
    const char *filename = argv[1];
    int w, h;

    //reading binary file
    struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);

    //modifies file name into new file name
    char newFilename[256];
    char* index = strrchr(filename, '.');  // Find last occurrence of '.'
    if (index != NULL) {
        // copying before .
        strncpy(newFilename, filename, index - filename);
        newFilename[index - filename] = '\0';

        // adding -glitch
        strcat(newFilename, "-glitch");
        strcat(newFilename, index); 
    }

    printf("Reading %s with width %d and height %d\n", filename, w, h);
    srand(time(NULL));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pixels[i][j].red =  pixels[i][j].red << (rand() % 2);   
            pixels[i][j].green = pixels[i][j].green << (rand() % 2); 
            pixels[i][j].blue = pixels[i][j].blue << (rand() % 2);   
        }
    }

    printf("Writing file %s\n", newFilename);
    write_ppm_2d(newFilename, pixels, w, h);
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    return 0;
}
