/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/14/2025
 * Description: Checks to see if a square is a magic square
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int isMagic(int** input, int rows, int cols){
  int sum = 0;
    for (int j = 0; j < cols; j++) {
        sum += input[0][j];
    }
    for (int i = 1; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += input[i][j];
        }
        if (row_sum != sum) return 0;
    }
    return sum;
}

int main() {
  int rows;
  int cols;
  scanf("%d", &rows);
  scanf("%d", &cols);

  int** matrix = malloc(sizeof(int*) * rows);
  for (int i = 0; i < rows; i++) {
    matrix[i] = malloc(cols * sizeof(int));
  }

  for( int i = 0; i < rows; i++){
    for( int j = 0; j < cols; j++){
      int number;
      scanf("%d", &number);
      matrix[j][i] = number;
      printf("%d ", matrix[j][i]);
    }
    printf("\n");
  }

  if( isMagic(matrix, rows, cols) == 0){
    printf("M is NOT a magic square!\n");
  } else {
    printf("M is a magic square (magic constant = %d)\n", isMagic(matrix, rows, cols));
  }
}
