/*----------------------------------------------
 * Author: Maxfield Ma
 * Date: 2/19/2025
 * Description: It lets the user input snacks and sorts it alphabetically using linked lists, or by quantity, or by price
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//just a snack struct. contains info about the snack and which snack is after it
struct snack{
    char name[50];
    float cost;
    int quantity;
    struct snack* next;
};

//function to add a snack to the snackbar. 
struct snack* insert_first(struct snack* head, char* name, float cost, int quantity){
    //creating a new snack
    struct snack* new_snack = malloc(sizeof(struct snack));

    //copying over all of the information about the snack
    strcpy(new_snack->name, name);
    new_snack->cost = cost;
    new_snack->quantity = quantity;

    //this puts this snack at the start of the linked list.
    new_snack->next = head;

    return new_snack;
}

//simple function, frees entire snack bar
void clear(struct snack* head){
    //temporary holder
    struct snack* next;

    //keeps freeing nodes until there are no more left.
    while(head){
        next = head;
        head = head->next;
        free(next);
    }
}

//quick function to print the entire linked list.
void printList(struct snack* head) {
    //temporary holder
    struct snack* temp = head;

    //counter
    int index = 0;

    //cycles through entire linked list and prints the info with nice formatting :D
    while (temp) {
        printf("%d) %-15s\t cost: $%-10.2f quantity: %-10d\n", index, temp->name, temp->cost, temp->quantity);
        temp = temp->next;
        index++;
    }
}

//tried using insertion sort, was too complicated, couldnt figure out double pointers (im like 99% sure you need to use that)
//made using selection sort
struct snack* sortCost(struct snack* head) {
    //failsafe, if not enough stuff just return it i.e. already sorted
    if (!head || !head->next){
        return head;
    }

    //temporary structs to find where each linked element belongs in the list
    struct snack* i;
    struct snack* j;
    struct snack* min;

    //loops through entire list i.e. while i and i->next exists
    for (i = head; i && i->next; i = i->next) {
        min = i;
        for (j = i->next; j; j = j->next) {
            if (j->cost < min->cost) {
                //storing the minimum cost
                min = j;
            }
        }
        //i decided to swap the information in nodes, rather than changing the order of nodes
        //because i couldnt figure out how double pointers worked.
        if (min != i) {
            //temporary holders
            float tempCost = i->cost;
            int tempQuantity = i->quantity;
            char tempName[50];

            //copying all the information
            strcpy(tempName, i->name);
            i->cost = min->cost;
            i->quantity = min->quantity;
            strcpy(i->name, min->name);

            min->cost = tempCost;
            min->quantity = tempQuantity;
            strcpy(min->name, tempName);
        }
    }
    return head;
}

//identical function to the one above, just sorting by name
struct snack* sortName(struct snack* head) {
    if (!head || !head->next){
        return head;
    }

    struct snack* i, * j, * min;
    for (i = head; i && i->next; i = i->next) {
        min = i;
        for (j = i->next; j; j = j->next) {
            //https://www.geeksforgeeks.org/strcmp-in-c/, compares strings lexicographically
            if (strcmp(j->name, min->name) < 0) {
                min = j;
            }
        }
        if (min != i) {
            char tempName[50];
            float tempCost = i->cost;
            int tempQuantity = i->quantity;

            strcpy(tempName, i->name);
            i->cost = min->cost;
            i->quantity = min->quantity;
            strcpy(i->name, min->name);

            min->cost = tempCost;
            min->quantity = tempQuantity;
            strcpy(min->name, tempName);
        }
    }
    return head;
}

//same thing but with quantity
struct snack* sortQuantity(struct snack* head) {
    if (!head || !head->next){
        return head;
    }

    struct snack* i, * j, * min;
    for (i = head; i && i->next; i = i->next) {
        min = i;
        for (j = i->next; j; j = j->next) {
            if (j->quantity < min->quantity) {
                min = j;
            }
        }
        if (min != i) {
            float tempCost = i->cost;
            int tempQuantity = i->quantity;
            char tempName[50];

            strcpy(tempName, i->name);
            i->cost = min->cost;
            i->quantity = min->quantity;
            strcpy(i->name, min->name);

            min->cost = tempCost;
            min->quantity = tempQuantity;
            strcpy(min->name, tempName);
        }
    }
    return head;
}


int main() {
    //variables for easy use
    int amount;
    char name[50];
    float cost;
    int quantity;

    printf("Enter number of snacks: ");
    scanf("%d", &amount);

    //start of snackBar
    struct snack* snackBar = NULL;

    //looping through desired amount of snacks and storing them in their respective place
    for(int i = 0; i < amount; i++){
        printf("Enter a name: ");
        scanf("%s", name);
        printf("Enter a cost: $");
        scanf("%f", &cost);
        printf("Enter a quantity: ");
        scanf("%d", &quantity);

        //adding each snack.
        snackBar = insert_first(snackBar, name, cost, quantity);
    }

    //printed these out just to test.
    printf("\nSnackbar:\n");
    printList(snackBar);
    
    snackBar = sortCost(snackBar);
    printf("\ncost:\n");
    printList(snackBar);
    
    snackBar = sortName(snackBar);
    printf("\nname:\n");
    printList(snackBar);
    
    snackBar = sortQuantity(snackBar);
    printf("\nquantity:\n");
    printList(snackBar);

    //function to free snackbar
    clear(snackBar);
    return 0;
}
