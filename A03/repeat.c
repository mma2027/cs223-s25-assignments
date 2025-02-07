/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 
 * Description
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char* repeat(char* input, int amount){
    char* newWord = malloc(strlen(input)*amount+1);

    if(!newWord){
        return NULL;
    }

    for( int i = 0; i < strlen(input)*amount; i++){
        newWord[i] = input[i % strlen(input)];
    }
    newWord[strlen(newWord)] = '\0';
    return newWord;
}

int main() {
    char word[32];
    int count;
    printf("Enter a word: ");
    scanf("%s", word);
    printf("Enter a count: ");
    scanf("%d", &count);
    char* newWord = repeat(word, count);
    if(newWord){

    
        printf("Your word is %s\n", newWord);
        free(newWord);
    } else {
        
        printf("Cannot allocate new string. Exiting...\n");
    }


  return 0;
}
