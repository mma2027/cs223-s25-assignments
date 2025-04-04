// Author: Maxfield Ma
// Date: 4/4/2025
// Description: Simple marco polo program. parent sends signal to child and child responds


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

//parent id
pid_t parentID;

//marco and polo funcitons
void marco(){
    printf("Marco [%d]\n", getpid());
    kill(parentID, SIGALRM);
}
void polo(){
    printf("Polo [%d]\n", getpid());
}


int main()
{
    parentID = getpid();
    char ch;
    printf("Parent is %d\n", getpid());
    pid_t pid = fork();
    if (pid == 0){
        signal(SIGALRM, marco);
        while (1){
        }
    } else {
        signal(SIGALRM, polo);
        while (1){
            ch = getchar();
            if (ch == 'm') {
                kill(pid, SIGALRM);
            } else if (ch == 'q'){
                kill(pid, SIGTERM);
                break;
            }
        }
    }
    wait(NULL);
    return 0;
}
