/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Simple program to test the read function
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
    int w, h;

    //reading
    struct ppm_pixel** pixels = read_ppm_2d("feep-raw.ppm", &w, &h);
    
    //some failsafes when I was working on the program
    if (!pixels) {
        printf("Failed to read PPM file.\n");
        return 1;
    }

    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    //printing what it read
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("(%d,%d,%d) ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
        }
        printf("\n");
    }

    // freeing array
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    return 0;
}