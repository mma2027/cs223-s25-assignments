#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel** image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  struct ppm_pixel** image = data->image;
  printf("Thread is coloring rows %d to %d with color: %d %d %d\n", data->starti, data->endi, data->color.red, data->color.blue, data->color.green);

  for( int i = data->starti; i < data->endi; i++){
    for( int j = 0; j < 1024; j++){
      image[i][j].red = data->color.red;
      image[i][j].blue = data->color.blue;
      image[i][j].green = data->color.green;

    }
  }
  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  int size = 1024;
  struct ppm_pixel **image = malloc(size * sizeof *image);
  for (int i = 0; i < size; i++)
      image[i] = malloc(size * sizeof *image[i]);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);

  int stripesPerThread = 1024 / N + 1;
  for (int i = 0; i < N; i++) {
    data[i].starti = i * stripesPerThread;
    if( data[i].starti > 1024){
      data[i].starti = 1024;
    }
    data[i].endi = (i + 1) * stripesPerThread;
    if( data[i].endi > 1024){
      data[i].endi = 1024;
    }
    colors[i].red = rand() % 255;
    colors[i].blue = rand() % 255;
    colors[i].green = rand() % 255;
    data[i].color = colors[i];
    data[i].image = image;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm_2d("stripes.ppm", image, size, size);

  for (int i = 0; i < size; i++) {
    free(image[i]);
  }
  free(image);
  free(colors);
  free(threads);
  free(data);
}
