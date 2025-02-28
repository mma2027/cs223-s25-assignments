/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/28/2025
 * Description: Reads a file and finds unmatched curly brackets {}
 ---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node info
struct node{
    char brace;
    int line;
    int col;
    struct node* next;
};

//stack
struct node* stack = NULL;

//add nodes to the stack
void push(char brace, int line, int col){
    struct node* newNode = malloc(sizeof(struct node));
    if(!newNode){
        printf("Stack Overflow Error");
        return;
    }
    newNode->brace = brace;
    newNode->next = stack;
    newNode->line = line;
    newNode->col = col;
    stack = newNode;
}

//pop function like in other languages
struct node* pop(){
    if(stack == NULL){
        return NULL;
    }
    struct node* temp = stack;
    stack = stack->next;
    return temp;
}

//freeing memory func
void clearStack(){
    while(stack != NULL){
        struct node* temp = stack;
        stack = stack->next;
        free(temp);
    }
}

//printing with line and col numbers for debugging
void printStack(){
    struct node* temp = stack;
    while(temp != NULL){
        printf("%c Line: %d Col: %d\n", temp->brace, temp->line, temp->col);
        temp = temp->next;
    }
}

int main(int argc, char *argv[]) {
    //looking for correct amount of arguments
    if (argc != 2) {
        printf("Usage: ./match_braces *filename*\n");
        return 0;
    }

    const char *filename = argv[1];
    int line = 1;
    int col = 1;

    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Filename invalid\n");
        return 0;
    }

    //character it gets from file
    char ch;

    //loop until end of file
    while((ch = fgetc(fp)) != EOF){
        //new line means reset column
        if(ch == '\n'){
            line += 1;
            col = 0;
        } else if (ch == '{'){
            push(ch, line, col);
        } else if (ch == '}'){
            struct node* temp = pop();
            //finding a closing brace with nothing in stack means unmatched brace
            if(temp == NULL){
                printf("Unmatched brace on Line %d and Column %d\n", line, col);
            } else {
                printf("Found matching braces: (%d, %d) -> (%d, %d)\n", temp->line, temp->col, line, col);
            }
            free(temp);
        }
        col += 1;
    }

    //leftover stuff in stack means its unmatched brace
    while(stack != NULL){
        struct node* temp = pop();
        if(temp == NULL){
            return 0;
        }
        printf("Unmatched brace on Line %d and Column %d\n", temp->line, temp->col);
        free(temp);
    }

    //printing and freeing
    printStack();
    clearStack();
    fclose(fp);
    return 0;
}