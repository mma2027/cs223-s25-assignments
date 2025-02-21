/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 02/21/2025
 * Description: Reads a 2d binary file in pixel format. Returns a pointer to the array storing the information.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// Choose *one* to implement (do not remove the other one!)

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  return NULL;
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {
    FILE* fp = fopen(filename, "rb");
    if(fp == NULL){
        printf("Filename invalid\n");
        return NULL;
    }
    char header[3];
    fgets(header, sizeof(header), fp);
    char buffer[100];
    
    //bypassing comment lines and such
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);
    
    //looks for width and height, returns null if cannot find
    if (fscanf(fp, "%d %d", w, h) != 2) {
        fclose(fp);
        return NULL;
    }
    //scaning for max val
    int max_val;
    fscanf(fp, "%d", &max_val);

    fgetc(fp); // the newline after max_val

    //These return NULL if there is not enough space to malloc
    struct ppm_pixel** pixels = malloc(*h * sizeof(struct ppm_pixel*));
    if (!pixels) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *h; i++) {
        pixels[i] = malloc(*w * sizeof(struct ppm_pixel));
        //checking if there is enough space
        if (!pixels[i]) {
            //freeing the rest
            for (int j = 0; j < i; j++) {
                free(pixels[j]);
            }
            free(pixels);
            fclose(fp);
            return NULL;
        }
    }
    
    //reads pixels
    for (int i = 0; i < *h; i++) {
        fread(pixels[i], sizeof(struct ppm_pixel), *w, fp);
    }

    //free/close FILE
    fclose(fp);
    return pixels;
}


