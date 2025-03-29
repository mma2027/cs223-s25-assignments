// Author : Maxfield Ma
// Date : 3/28/2025
// Description : Simple program that uses fork() to enhance the search of files for a keyword

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(int argc, char* argv[]) {
    if( argc < 4 ){
        printf("usage: ./grep <NumProcesses> <Keyword> <Files>\n");
        return 0;
    }

    //vars
    struct timeval start, end;
    double elapsed;
    int amount = 0;
    int curFile = 3;
    int totalFile = argc - 3;
    int filePerFork = (totalFile + atoi(argv[1]) - 1) / atoi(argv[1]);
    
    //start timer
    gettimeofday(&start, NULL);

    //creating child processes
    for( int i = 0; i < atoi(argv[1]); i++){
        pid_t pid = fork();

        //if child processes continue, else dont
        if (pid == 0){
            printf("Searching %d files for keyword: %s\n", argc-3, argv[2]);

            //calculating which files the child needs to search
            int fileStart = 3 + i * filePerFork;
            int fileEnd = fileStart + filePerFork;
            if (fileStart > argc){
                fileStart = argc;
            }
            if (fileEnd > argc){
                fileEnd = argc;
            }

            printf("Process [%d] searching %d files (%d - %d)\n", getpid(), fileEnd - fileStart, fileStart, fileEnd);

            //searching each file
            for( int i = fileStart; i < fileEnd; i++ ){
                FILE* fp = fopen(argv[i], "r");
                if( fp == NULL ){
                    printf("Process [%d] Error: Cannot open file\n", getpid());
                    exit(0);
                } else {
                    //vars for neat printing in red color :)
                    char buffer[100];
                    char *index;
                    char *temp = buffer;

                    //searching all of the file
                    while(fgets(buffer, sizeof(buffer), fp) != NULL){
                        if((index = strstr(buffer, argv[2])) != NULL){
                            amount = amount + 1;
                            printf("%.*s", (int)(index-temp), temp);
                            printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, argv[2]);
                            printf("%s", index + strlen(argv[2]));
                        }
                    }
                }
                fclose(fp);
            }
            //return amount
            printf("Process [%d] found %d lines containing keyword: %s\n", getpid(), amount, argv[2]);
            exit(amount);
        }
    }

    //waiting for each child process created to return something
    for (int i = 0; i < atoi(argv[1]); i++) {
        int status;
        waitpid(-1, &status, 0);
        //just checking that it did exit with a count (in the case it cannot open the file)
        if (WIFEXITED(status)) {
            amount += WEXITSTATUS(status);
        }
    }

    printf("Total occurances: %d\n", amount);

    //calculate time took in miliseconds
    gettimeofday(&end, NULL);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Elapsed time: %f ms\n", elapsed);
    return 0;
}
