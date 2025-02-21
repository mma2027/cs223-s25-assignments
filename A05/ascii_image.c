/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Turns a simple ppg image into ascii art by intensity
 ---------------------------------------------*/
#include <stdio.h>
#include "read_ppm.h"
#include "write_ppm.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    //takes in file input
    const char *filename = argv[1];
    int w, h;

    //reading binary file
    struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);

    printf("Reading %s with width %d and height %d\n", filename, w, h);

    printf("Sample pixel data (Top-left corner):\n");
    for (int i = 0; i < 5 && i < h; i++) {  // print top 5 rows (if possible)
        for (int j = 0; j < 5 && j < w; j++) {  // print first 5 columns (if possible)
            printf("(%d, %d, %d) ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
        }
        printf("\n");
    }
    //for each pixel prints a character based on intensity
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // character selection
            if( (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 25){
                printf("@");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 50) {
                printf("#");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 75) {
                printf("%c", '%');
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 100) {
                printf("*");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 125) {
                printf("o");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 150) {
                printf(";");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 175) {
                printf(":");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 200) {
                printf(",");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 225) {
                printf(".");
            } else if ((pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3 <= 255) {
                printf(" ");
            }
        }
        printf("\n");
    }

    //freeing the array
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    return 0;
}
