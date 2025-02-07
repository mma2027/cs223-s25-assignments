/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/7/2025
 * Description: Asks for a simple word and then prints back the word repeated a desired amount of times.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//function to allocate space for the new word and to set the values of the space to create the new word
char* repeat(char* input, int amount){
    char* output = malloc(strlen(input)*amount+1);

    //failsafe if not enough space
    if(!output){
        return NULL;
    }

    //function to loop through original word and set the new word indexes to be the same
    for( int i = 0; i < strlen(input)*amount; i++){
        output[i] = input[i % strlen(input)];
    }

    //null terminate str
    output[strlen(input) * amount] = '\0';
    return output;
}

int main() {
    char word[32];
    int count;

    printf("Enter a word: ");
    scanf("%s", word);
    printf("Enter a count: ");
    scanf("%d", &count);

    //storing new word
    char* newWord = repeat(word, count);

    //failsafe
    if(newWord){
        printf("Your word is %s\n", newWord);
    } else {
        printf("Cannot allocate new string. Exiting...\n");
    }

    //freeing up the space again
    free(newWord);
    return 0;
}
