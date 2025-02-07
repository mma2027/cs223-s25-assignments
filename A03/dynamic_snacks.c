/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/7/2025
 * Description: Allows the user to create their own snackbar complete with names, cost, and quantity. Then prints menu.
 ---------------------------------------------*/

 //Testing
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack{
    char name[50];
    float cost;
    int quantity;
};

//quick function to print out the snack menu with some nice formatting :D
void printInfo( struct snack bar[], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d) %-15s\t cost: $%-10.2f quantity: %-10d\n", 
                i, bar[i].name, bar[i].cost, bar[i].quantity);
    }
}


int main() {
    int amount;
    
    printf("Enter number of snacks: ");
    scanf("%d", &amount);

    //allocating space for the entire struct
    struct snack* snackBar = malloc(sizeof(struct snack) * amount);

    //looping through desired amount of snacks and storing them in their respective place
    for(int i = 0; i < amount; i++){
        printf("Enter a name: ");
        char name[50];
        scanf("%s", snackBar[i].name);
        printf("Enter a cost: $");
        scanf("%f", &snackBar[i].cost);
        printf("Enter a quantity: ");
        scanf("%d", &snackBar[i].quantity);
    }

    //printing..
    printf("\nWelcome to Dynamic Donna's Snack Bar\n");
    printInfo( snackBar, amount);

    //freeing up space again
    free(snackBar);
  return 0;
}
