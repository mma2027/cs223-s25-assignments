/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/28/2025
 * Description: Some basic functions to create and look through binary trees
 ---------------------------------------------*/

#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

//searches left branches first then right branches recursively
struct tree_node* find(const char* name, struct tree_node* root)
{
    if (root == NULL) {
        return NULL;
    }

    if( strcmp(name, root->data.name) == 0 ){
        return root;
    }
    
    struct tree_node* temp = find(name, root->left);

    if (temp != NULL){
        return temp;
    }

    return find(name, root->right);
}

//inserts node recursively
struct tree_node* insert(const char* name, struct tree_node* root)
{
    
    if (root == NULL){
        struct tree_node* newTreeNode = malloc(sizeof(struct tree_node));
        strcpy(newTreeNode->data.name, name);
        newTreeNode->left = NULL;
        newTreeNode->right = NULL;

        return newTreeNode;
    }
    
    if (strcmp(name, root->data.name) < 0){
        root->left = insert(name, root->left);
    } else {
        root->right = insert(name, root->right);
    }

    return root;
}

//frees everything
void clear(struct tree_node* root)
{
    if (root == NULL) {
        return;
    }
    clear(root->left);
    clear(root->right);
    free(root);
}

//just a function to print text to match the formatting in the example
static void printHelper(struct tree_node* root, int level, const char* prefix) {
    if (root == NULL) return;
    
    for (int i = 0; i < level; i++) {
        printf(" ");
    }
    
    //just a thing to match the format of example
    if (prefix != NULL) {
        printf("%s", prefix);
    }

    printf("%s\n", root->data.name);
    
    if (root->left != NULL) {
        printHelper(root->left, level + 1, "l:");
    }
    if (root->right != NULL) {
        printHelper(root->right, level + 1, "r:");
    }
}

//print the whole tree
void print(struct tree_node* root) {
    printHelper(root, 0, "");
}

//print the data in order
void printSorted(struct tree_node* root)
{
    if (root == NULL) {
        return;
    }
    printSorted(root->left);
    printf("%s\n", root->data.name);
    printSorted(root->right);
}