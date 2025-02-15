/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/14/2025
 * Description: Checks to see if a square is a magic square, if it is, returns the magic number
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function to check if the sum of every row and collum is the same.
int isMagic(int** input, int rows, int cols){
    int sum = 0;
    //finds the sum of a colm
    for (int j = 0; j < cols; j++) {
        sum += input[0][j];
    }

    //checks if all rows sum to the same sum
    for (int i = 1; i < rows; i++) {
        int row_sum = 0;
        for (int j = 0; j < cols; j++) {
            row_sum += input[i][j];
        }
        if (row_sum != sum){
            return 0;
        }
    }

    //checks if all cols sum to the same sum
    for (int i = 1; i < cols; i++) {
        int col_sum = 0;
        for (int j = 0; j < rows; j++) {
            col_sum += input[j][i];
        }
        if (col_sum != sum) {
            return 0;
        }
    }
    
    //checks both diaganol sums
    int diag_sum = 0;
    int diag_sum2 = 0;
    for (int i = 0; i < rows; i++){
        diag_sum += input[i][i];
        diag_sum2 += input[i][cols-i-1];
    }
    if (diag_sum != sum || diag_sum2 != sum){
        return 0;
    }
    return sum;
}

int main() {
    int rows;
    int cols;
    //gathering information
    scanf("%d", &rows);
    scanf("%d", &cols);

    //allocating space in heap for pointers
    int** matrix = malloc(sizeof(int*) * rows);
    //allocating space in heap for elements
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
    }

    //gathering more info and printing matrix
    for( int i = 0; i < rows; i++){
        for( int j = 0; j < cols; j++){
            int number;
            scanf("%d", &number);
            matrix[j][i] = number;
            printf("%d ", matrix[j][i]);
        }
        printf("\n");
    }

    //checking if M is magic or not
    if( isMagic(matrix, rows, cols) == 0){
        printf("M is NOT a magic square!\n");
    } else {
        printf("M is a magic square (magic constant = %d)\n", isMagic(matrix, rows, cols));
    }

    //freeing everything
    for (int i = 0; i < rows; i++) {
        free( matrix[i]);
    }
    free(matrix);
}
