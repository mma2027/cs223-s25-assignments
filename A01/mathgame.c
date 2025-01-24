/***************************************************
 * mathgame.c
 * Author: Maxfield Ma
 * Date: 1/24/2025
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Welcome to Math Game!\n");
    printf("How many rounds do you want to play? ");
    int amountOfRounds = 0;
    scanf("%d", &amountOfRounds);

    //initializing all the variables used
    short number1;
    short number2;
    short answer;
    short correctAnswers = 0;

    for (int i = 0; i < amountOfRounds; i++) {
        //setting the two numbers to a random value between 1 - 10
        number1 = rand() % 9 + 1;
        number2 = rand() % 9 + 1;

        printf("\n%hi + %hi = ? ", number1, number2);
        scanf("%hi", &answer);

        if (answer == number1 + number2) {
            printf("Correct!\n");
            correctAnswers += 1;
        } else {
            printf("Incorrect :(\n");
        }
    }

    printf("You answered %hi/%hi correctly.\n", correctAnswers, amountOfRounds);
    return 0;
}
