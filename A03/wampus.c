/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/7/2025
 * Description: Prints a wampus on a board with desired dimensions and fills the board with the distance to the wampus
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//  simple function to convert an integer into its (x,y) coordinates on the grid 
//  and then use that to calculate its distance from the wampus
int calcVal(int curPos, int desiredPos, int rows, int cols){
    int curCol = curPos % cols;
    int curRow = ( curPos - curCol ) / rows;
    int finalCol = desiredPos % cols;
    int finalRow = (desiredPos - finalCol ) / rows;
    
    return abs(curRow - finalRow) + abs(curCol - finalCol);
}


int main() {
    int rows;
    int cols;

    srand(time(NULL));

    printf("Number of rows: ");
    scanf("%d", &rows);
    printf("Number of columns: ");
    scanf("%d", &cols);

    char* grid = malloc(rows * cols + 1);

    //random placement of wampus
    int w = rand() % (rows * cols);

    //filling up the allocated memory
    for( int i = 0; i < rows * cols; i++){
        if( calcVal(i, w, rows, cols) == 0){
            grid[i] = 'W';
        } else {
            grid[i] = calcVal(i, w, rows, cols);
        }
    }

    //null terminate string
    grid[rows * cols] = '\0';

    //print string into a grid
    for( int i = 0; i < rows; i++ ){
        for ( int j = 0; j < cols; j++ ){
            if(grid[i*cols + j] == 'W'){
                printf("W ");
            } else {
                printf("%d ", grid[i * cols + j]);
            }
        }
        printf("\n");
    }

    //freeing the space again
    free(grid);
    return 0;
}
