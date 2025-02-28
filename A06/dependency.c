/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/28/2025
 * Description: Creates some binary trees and identifies dependencies
 ---------------------------------------------*/
 
#include <stdio.h>
#include "tree.h"
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    printf("Processing %d files\n", argc - 1);

    struct tree_node* root = NULL;

    //inserting the list of valid files
    for( int i = 1; i < argc; i++){
        FILE* fp = fopen(argv[i], "r");
        if( fp != NULL){
            root = insert(argv[i], root);
        }
        fclose(fp);
    }

    //making custom commands with a while loop
    char input[256];
    while (1) {
        //looks nice
        printf("$ ");

        //failsafes
        if (fgets(input, sizeof(input), stdin) == NULL){
            break;
        }

        //ignore new  lines replaces the enter with the null terminator to fix issue with pushing enter for commands
        input[strcspn(input, "\n")] = '\0';

        //looking for command quit, list, otherwise its searching for a file name
        if (strcmp(input, "quit") == 0) {
            break; 
        } else if (strcmp(input, "list") == 0) {
            printSorted(root);
        } else {
            struct tree_node* temp = find(input, root);

            //if it cant find the file
            if( temp == NULL ){
                printf("%s not found\n", input);
            } else {
                printf("%s has the following dependencies\n", input);
                FILE* fp = fopen(input, "r");
                //failsafe
                if(fp == NULL){
                    printf("Cannot open file\n");
                } else {
                    char line[256];
                    while(fgets(line, sizeof(line), fp) != NULL){
                        if( strstr(line, "#include") != NULL){
                            //match formatting in the example
                            printf("  ");
                            printf("%.*s\n", (int)(strlen(line) - 13), line + 10);
                        }
                    }
                    fclose(fp);
                }
            }
        }
    }
    //freeing memory
    clear(root);
}
