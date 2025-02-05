// Authors: Maxfield Ma, Gabby Stewart
// Date: 2/4/25
// Intent: Dishwasher guessing game!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//simple program to keep track of the value of the current winning guess without going over
int compare( int a, int b, int price){
    if (a > price && b > price){
        return price + 1;
    } else if (a > price) { 
        return b;
    } else if (b > price) {
        return a;
    } else if (price - a < price - b) {
        return a;
    } else {
        return b;
    }
}

//formats the guesses in a nice way
void printGuesses( int ai1, int ai2, int guess, int price ){
    printf("\nAI #1 Guess    :  $%i\n", ai1);
    printf("AI #2 Guess    :  $%i\n", ai2);
    printf("Your Guess     :  $%i\n", guess);
    printf("Actual Price   :  $%i\n\n", price);
}

int main()
{
    //variables
    srand(time(NULL));
    int guess;
    int price = rand() % 2001 + 3000;
    int ai1 = rand() % 2001 + 3000;
    int ai2 = rand() % 2001 + 3000;
    //running total of the closest winning guess
    int win;

    printf("Welcome to the Price is Right!");
    printf("\nEnter a guess to win a luxurious dishwasher: $");
    scanf("%i", &guess);

    //figure out the value of the winning guess
    win = compare(guess, ai1, price);
    win = compare(win, ai2, price);

    //some formatting!
    printGuesses(ai1, ai2, guess, price);

    //figure out who had the winning guess
    if( win > price){
        printf("No one won the dishwasher as you all guessed too high!");
    } else if(win == guess){
        printf("Congratulations! You won!\n");
    } else if(win == ai1){
        printf("AI #1 Won!\n");
    } else {
        printf("AI #2 Won!\n");
    }
    return 0;
}

