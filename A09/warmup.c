// Author : Maxfield Ma
// Date : 3/28/2025
// Description : Simple program that creates childs that prints text


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    printf("%d] A0\n", getpid());

    //creating child
    pid_t pid = fork();
    if (pid != 0){
        printf("%d] B0\n", getpid());

        //creating another child
        pid_t pid2 = fork();
        if( pid2 == 0 ){
            printf("%d] C0\n", getpid());
        } else {
            printf("%d] C1\n", getpid());
        }
    } else {
        printf("%d] B1\n", getpid());
    }

    //all lines print Bye
    printf("%d] Bye\n", getpid());
    return 0;
}
