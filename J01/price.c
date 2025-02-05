#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//simple program to keep track of the value of the current winning guess
int compare( int a, int b, int price){
   if (a > price && b > price){
      return price + 1;
   } else if (a > price) { 
      return b;
   } else {
      return a;
   }
}


int main()
{
   srand(time(NULL));
   int guess;
   int price = rand() % 2001 + 3000;
   int ai1 = rand() % 2001 + 3000;
   int ai2 = rand() % 2001 + 3000;

   int win;

   printf("Welcome to the Price is Right!");
   printf("\nEnter a guess to win a luxurious dishwasher: ");
   scanf("%i", &guess);

   win = compare(guess, ai1, price);
   win = compare(win, ai2, price);

   printf("\n%i %i %i %i", guess, ai1, ai2, price);

   //figure out who had the winning guess
   if( win > price){
      printf("No one won");
   } else if( win == guess){
      printf("You won");
   } else if( win == ai1){
      printf("ai1 won");
   } else {
      printf("ai2 won");
   }
   return 0;
}

