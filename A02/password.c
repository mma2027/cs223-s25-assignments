/***************************************************
 * Author: Maxfield Ma
 * GitHub: mma2027
 * Intent: creates a bad password from a word
 * Date: 1/31/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* createBadPassword (char oldPassword[]) {
    //creating space for new password and copying the old password over
    char* newPassword = malloc(strlen(oldPassword) + 1);
    strcpy(newPassword, oldPassword);

    //replacing desired values e,l,a in old password to create new password with symbols
    for (int i = 0; i < strlen(oldPassword); i++) {
        if (oldPassword[i] == 'e') {
            newPassword[i] = '3';
        } else if (oldPassword[i] == 'l') {
            newPassword[i] = '1';
        } else if (oldPassword[i] == 'a') {
            newPassword[i] = '@';
        }
    }

    return newPassword;
}

int main() {
    //making sure word is long enough
    char word[100];

    printf("Enter a word: ");
    scanf("%s", word);

    //storing password created from word
    char* badPassword = createBadPassword(word);
    printf("Your bad password is %s\n", badPassword);

    //"freeing" malloc
    free(badPassword);
    return 0;
}
