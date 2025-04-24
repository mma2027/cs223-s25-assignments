#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 32

int main()
{
    int bool = 0;
    int number = 0;
    printf("Boolean: ");
    scanf(" %d", &bool);
    printf("Number: ");
    scanf(" %d", &number);
    char* boolStr = " ";
    if (bool == 0){
        boolStr = "false";
    } else {
        boolStr = "true";
    }
    char** adj = malloc(sizeof(char *) * number);
    for( int i = 0; i < number; i++){
        adj[i] = malloc(sizeof(char) * 32);
    }

    for( int i = 0; i < number; i++){
        printf("Adjective: ");
        scanf(" %31s", adj[i]);
    }
    printf("You are the most ");
    for( int i = number - 1; i > 0; i--){
        printf("%s, ", adj[i]);
    }
    printf("and %s person that I know and you know it's %s.", adj[0], boolStr);

    for( int i = 0; i < number; i++){
        free(adj[i]);
    }
    free(adj);
    return 0;
}
