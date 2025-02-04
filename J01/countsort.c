// Author: Maxfield Ma, Gabby Stewart
// Date: 2/4/25
// Intent: Sorts digits from a string


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char* input){
   char sortedDigits[32];
   int index = 0;
   
   //looks for characters and adds them to sortedDigits
   for( int i = '0'; i <= '9'; i++){
      for( int j = 0; j < strlen(input); j++ ){
         if( input[j] == i ) {
            sortedDigits[index] = i;
            index++;
         }
      }
   }

   //replace input with sortedDigits
   strcpy(input, sortedDigits);
}




int main()
{
   char digits[32];

   printf("Enter digits: ");
   scanf("%s", digits);

   sort(digits);

   printf("%s\n", digits);
   return 0;
}
