/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 03/7/2025
 * Description: Encodes an image with a secret message
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
    //argument usage
    if (argc != 2) {
        printf("usage: encode <file.ppm>\n");
        return 0;
    }

    //filename
    char* filename = argv[1];

    //vars
    int w, h;
    int maxChar = 0;
    char newFilename[256];
    
    //reading
    struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);
    if (!pixels) {
        printf("Failed to read PPM file.\n");
        return 1;
    }

    //copied from glitch.c - creates new file name
    char* index = strrchr(filename, '.');
    if (index != NULL) {
        strncpy(newFilename, filename, index - filename);
        newFilename[index - filename] = '\0';

        strcat(newFilename, "-encoded");
        strcat(newFilename, index); 
    }

    printf("Reading %s with width %d and height %d\n", argv[1], w, h);
    maxChar = (w * h * 3) / 8;

    //more vars
    char* phrase = malloc(sizeof(char) * maxChar); //phrase to be encoded
    int* binaryPhrase = malloc(sizeof(int) * maxChar * 8); //binary version of phrase
    memset(binaryPhrase, 0, sizeof(int) * maxChar * 8);

    printf("Max number of characters in the image: %d\n", maxChar - 1);
    printf("Enter a phrase: ");
    scanf(" %s", phrase);


    //check string length
    if( strlen(phrase) > maxChar ){
        printf("Phrase is too long to encode in this image.\n");
        return 0;
    }
    

    //turning phrase into binary
    for( int i = 0; i < strlen(phrase); i++){
        for ( int j = 0; j < 8; j++){
            if( ((phrase[i] >> j) & 1) == 1 ){
                binaryPhrase[8 * i + 7 - j] = 1;
            } else {
                binaryPhrase[8 * i + 7 - j] = 0;
            }
        }
    }

    //encoding pixels
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            pixels[i][j].red =  ((pixels[i][j].red >> 1) << 1) | binaryPhrase[(w * 3 * i) + (3 * j)];   
            pixels[i][j].green = ((pixels[i][j].green >> 1) << 1) | binaryPhrase[(w * 3 * i) + (3 * j) + 1]; 
            pixels[i][j].blue = ((pixels[i][j].blue >> 1) << 1) | binaryPhrase[(w * 3 * i) + (3 * j) + 2];
        }
    }

    printf("Writing file %s\n", newFilename);
    write_ppm_2d(newFilename, pixels, w, h);

    for (int i = 0; i < h; i++) {
        free(pixels[i]);
    }
    free(pixels);
    free(phrase);
    free(binaryPhrase);
    return 0;
}

