/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Simple program to test the write function
 ---------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
    int w, h;

    //reading binary file
    struct ppm_pixel** pixels = read_ppm_2d("feep-raw.ppm", &w, &h);
    printf("Testing file feep-raw.ppm: %d %d\n", w, h);

    //printing the information
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            printf("(%d,%d,%d) ", pixels[i][j].red, pixels[i][j].green, pixels[i][j].blue);
        }
        printf("\n");
    }

    // test writing the file to test.ppm
    write_ppm_2d("test.ppm", pixels, w, h);

    //freeing array
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    return 0;
}
