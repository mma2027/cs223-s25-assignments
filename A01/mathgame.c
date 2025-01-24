/***************************************************
 * mathgame.c
 * Author: Maxfield Ma
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("Welcome to Math Game! ");
	printf("How many rounds do you want to play? ");
	int amount_of_rounds = 0;
	scanf("%d", &amount_of_rounds);

	//initializing all the variables used
	int number1;
	int number2;
	int answer;
	int correct_answers = 0;

	for(int i = 0; i < amount_of_rounds; i++){
		//setting the two numbers to a random value between 1 - 10
		number1 = rand() % 9 + 1;
		number2 = rand() % 9 + 1;

		printf("%d + %d = ? ", number1, number2);
		scanf("%d", &answer);

		if (answer == number1 + number2){
			printf("Correct!\n");
			correct_answers += 1;
		} else {
			printf("Incorrect :(\n");
		}
	}

	printf("You answered %d/%d correctly.\n", correct_answers, amount_of_rounds);
	return 0;
}
