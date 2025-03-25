#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct meta_data
{
  float version;
  unsigned int year;
  unsigned int length;
};

void read(const char* filename) {
  FILE* fp = fopen(filename, "rb");
  if(fp == NULL){
      printf("Filename invalid\n");
  }
  char comment[40];
  fgets(comment, 40, fp);
  printf("header: %s", comment);

  struct meta_data* data = malloc(sizeof(struct meta_data));

  fread(data, sizeof(struct meta_data), 1, fp);


  printf("Version: %.2f\n", data->version);
  printf("Year: %d\n", data->year);
  printf("Length: %d\n", data->length);

  char* text = malloc((data->length + 1));
  fread(text, (data->length + 1), 1, fp);
  printf("Message: %s\n", text);
  fclose(fp);
  free(data);
  free(text);
}


int main(int argc, char* argv[])
{
  if ( argc != 2){
    printf("Usage: ./message_reader\n");
    return 0;
  }
  read(argv[1]);
  return 0;
}
