#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct meta_data
{
  float version;
  unsigned int year;
  unsigned int length;
};


void write(const char* filename) {
  // Open the file in binary write mode and return NULL if it can't be opened
  FILE *fp = fopen(filename, "wb");
  if (fp == NULL) {
      printf("Error opening file %s.\n", filename);
      return;
  }

  char *comment = "# comment\n";

  fwrite(comment, sizeof(char), strlen(comment), fp);

  struct meta_data* temp = malloc(sizeof(struct meta_data));
  temp->version = 0.1;
  temp->year = 1990;
  temp->length = 6;
  
  char* message = "hi :)";

  fwrite(temp, sizeof(struct meta_data), 1, fp);
  fwrite(message, sizeof(char), strlen(message), fp);

  fclose(fp);  // Close the file
  free(temp);
}

int main(int argc, char* argv[])
{
  if ( argc != 2){
    printf("Usage: ./message_wrter\n");
    return 0;
  }

  write(argv[1]);
  return 0;
}
