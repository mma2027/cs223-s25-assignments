/***************************************************
 * Author: Maxfield Ma
 * GitHub: mma2027
 * Date: 1/31/2025
 * Encrypts a word by shifting the alphabet a desired amount of spaces
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//function that encrypts the word
char* createCypher(char input[], int shift){

    //reserving space in the heap
    char* cypher = malloc(strlen(input)+1);

    //for loop to cycle through each letter in word
    for (int i = 0; i < strlen(input); i++) {
        // math equation to assign each lower case character 
        // a value between [0,25] to perform the shift seamlessly
        cypher[i] = (input[i] - 'a' + shift + 26) % 26 + 'a';
    }

    //prevent memory issues with valgrind
    cypher[strlen(input)] = '\0';
    return cypher;
}

int main() {
    //variables
    //making sure word is long enough
    char word[100];
    int shift;

    //collecting words and the shift amount
    printf("Enter a word: ");
    scanf("%s", word);
    printf("Enter a shift: ");
    scanf("%d", &shift);

    char* cypher = createCypher(word, shift);
    printf("Your cypher is %s\n", cypher);

    //freeing the space in heap
    free(cypher);
    return 0;
}
