// Author: Maxfield Ma, Gabby Stewart
// Date: 2/4/25
// Intent: Sorts digits from a string


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(char* input){
    char sortedDigits[32];
    //this index keeps track of the position in sortedDigits
    int index = 0;
   
    //looks for characters and adds them to sortedDigits
    //searching for characters 0-9
    for( int i = '0'; i <= '9'; i++){
        //searching for specified character in input
        for( int j = 0; j < strlen(input); j++ ){
            if( input[j] == i ) {
                sortedDigits[index] = i;
                index++;
            }
        }
    }
    //create a valid string (valgrind was having problems with this it seems)
    sortedDigits[index] = '\0';

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
