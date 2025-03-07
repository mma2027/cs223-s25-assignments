/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 03/07/2025
 * Description: Decodes a hidden message in an image
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
    //usage error
    if (argc != 2) {
        printf("usage: decode <file.ppm>\n");
        return 0;
    }

    //vars
    char* filename = argv[1];
    int w, h;
    int maxChar = 0;
    
    //reading
    struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);
    if (!pixels) {
        printf("Failed to read PPM file.\n");
        return 1;
    }
    printf("Reading %s with width %d and height %d\n", argv[1], w, h);
    maxChar = (w * h * 3) / 8;
    printf("Max number of characters in the image: %d\n", maxChar);

    //more vars
    int* ascii = malloc(sizeof(int) * maxChar* 8); //stores the least significant bit of each color, to be interpreted as ascii
    char* string = malloc(sizeof(char) * maxChar); //stores the decoded message

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            ascii[(w * 3 * i) + (3 * j)] = pixels[i][j].red % 2;
            ascii[(w * 3 * i) + (3 * j) + 1] = pixels[i][j].green % 2;
            ascii[(w * 3 * i) + (3 * j) + 2] = pixels[i][j].blue % 2;
        }
    }

    for( int i = 0; i < maxChar; i++){
        int sum = 0;
        for( int j = 0; j < 8; j++){
            sum = sum + (ascii[8 * i + 7 - j] << j);
        }
        string[i] = sum;
        if(sum == 0){
            break;
        }
    }

    printf("%s", string);

    //free
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    free(ascii);
    free(string);
    return 0;
}

