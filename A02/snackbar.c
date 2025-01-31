/***************************************************
 * Author: Maxfield Ma
 * GitHub: mma2027
 * Date: 1/31/2025
 * Intent: Displays Steven's Snack Bar menu and allows customer to purchase some snackies!
 */
#include <stdio.h>

//declaring that a snackbar has the names, cost and quantity of each snack
struct SnackBar {
    char* name;
    float cost;
    int quantity;
};

//quick function to print out the snackbar menu with some nice formatting :D
void printInfo( struct SnackBar bar[], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%d) %-15s\t cost: $%-10.2f quantity: %-10d\n", 
                i, bar[i].name, bar[i].cost, bar[i].quantity);
    }
}

int main() {

    //variables used
    float money;
    int snackChoice;

    ///declaring steven's snackbar prices and stock
    struct SnackBar steven[3] = { 
        {"Coco Puffs", 1.50, 4},
        {"Manchego cheese", 15.50, 6},
        {"Magic beans", 0.50, 0}
    };

    printf("Welcome to Steven Struct's Snack Bar.\n\n");
    printf("How much money do you have? ");
    scanf("%f", &money);

    //a way to determine how many elements are in struct
    printInfo(steven, sizeof(steven) / sizeof(steven[0]));

    printf("\nWhat snack would you like to buy? [0,1,2] ");
    scanf("%d", &snackChoice);

    //checking to see if you can actually buy it (instock or have enough money)
    if(steven[snackChoice].quantity <= 0){
        printf("Sorry, we are out of %s\n", steven[snackChoice].name);
    } else if (money-steven[snackChoice].cost < 0) {
        printf("You can't afford it!\n");
    } else {
        printf("\nYou bought %s\n", steven[snackChoice].name);
        printf("You have $%0.2f left\n", money-steven[snackChoice].cost);
    }

    return 0;
}
