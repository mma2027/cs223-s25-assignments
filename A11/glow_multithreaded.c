// Author : Maxfield Ma
// Date : 4/11/2025
// Description : Bluring an image using threads!

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

struct thread{
    pthread_t id;
    int N;
    int index;
    int w;
    int h;
    int threshold;
    int blurRadius;
    struct ppm_pixel** pixels;
    struct ppm_pixel** blur;
    struct ppm_pixel** bright;
    pthread_barrier_t *barrier;
};

void *glow( void *arg ){
    //transfering variables
    struct thread* t = (struct thread*) arg;
    int index = t->index;
    int w = t->w;
    int h = t->h;
    int N = t->N;
    int startH = (t->h / N) * index;
    int endH = (t->h / N) * (index + 1);

    struct ppm_pixel** pixels = t->pixels;
    struct ppm_pixel** blur = t->blur;
    struct ppm_pixel** bright = t->bright;
    
    printf("Thread sub-image slice: rows (%d, %d)\n", startH, endH);

    //finding bright spots
    for (int y = startH; y < endH; y++){
        for (int x = 0; x < w; x++){
            if (pixels[y][x].red + pixels[y][x].green + pixels[y][x].blue > t->threshold){
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

    //waiting till all threads are done.
    pthread_barrier_wait(t->barrier);

    //bluring bright spots
    for (int y = startH; y < endH; y++){
        for (int x = 0; x < w; x++){
            int startX = x - t->blurRadius;
            int endX = x + t->blurRadius + 1;
            int startY = y - t->blurRadius;
            int endY = y + t->blurRadius + 1;

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

    //waiting again
    pthread_barrier_wait(t->barrier);

    //adding back to original image
    for (int y = startH; y < endH; y++){
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
    return NULL;
}

int main(int argc, char* argv[]) 
{
    int N = 4;
    int threshold = 200;
    int blursize = 24;
    const char* filename = "earth-small.ppm";

    int opt;
    while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
        switch (opt) {
            case 'N': N = atoi(optarg); break;
            case 't': threshold = atof(optarg); break;
            case 'b': blursize = atof(optarg); break;
            case 'f': filename = optarg; break;
            case '?': printf("usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur size> -f <ppmfile>\n", argv[0]); break;
        }
    }
    // todo: your code here
    // compute image
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, NULL, N);
    int w;
    int h;

    //reading file
    struct ppm_pixel** pixels = read_ppm_2d(filename, &w, &h);

    //failsafe
    if (pixels == NULL) {
        printf("Error: Failed to read the image\n");
        return 1;
    }

    //creating threads array
    struct thread* threads = malloc(N * sizeof(struct thread));

    //creating blur and bright arrays
    struct ppm_pixel** blur = malloc(h * sizeof(struct ppm_pixel*));
    for (int i = 0; i < h; i++){
        blur[i] = malloc(w * sizeof(struct ppm_pixel));
        //checking if there is enough space
        if (!blur[i]) {
            //freeing the rest if not
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
            //freeing the rest if not
            for (int j = 0; j < i; j++) {
                free(bright[j]);
            }
            free(bright);
        }
    }

    int threshold_sum = threshold * 3;
    int blurRadius = blursize / 2;

    //creating threads
    for( int i = 0; i < N; i++){
        threads[i].index = i;
        threads[i].pixels = pixels;
        threads[i].h = h;
        threads[i].w = w;
        threads[i].N = N;
        threads[i].blur = blur;
        threads[i].bright = bright;
        threads[i].threshold = threshold_sum;
        threads[i].blurRadius = blurRadius;
        threads[i].barrier = &barrier;
        pthread_create(&threads[i].id, NULL, glow, &threads[i]);
    }

    //joining threads, removing barrier and writing file
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i].id, NULL);
    }
    pthread_barrier_destroy(&barrier);
    write_ppm_2d("glow.ppm", pixels, w, h);

    //free everything
    for (int i = 0; i < h; i++) {
        free(pixels[i]);
        free(blur[i]);
        free(bright[i]);
    }
    free(pixels);
    free(blur);
    free(bright);
    free(threads);
}
