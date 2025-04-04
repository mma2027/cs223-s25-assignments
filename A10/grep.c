// Author : Maxfield Ma
// Date : 4/4/2025
// Description : Simple program that uses threads to enhance the search of files for a keyword
#include <pthread.h>
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

//struct for holding important information for the arguments of the thread function
struct threadArg {
    int threadIndex;
    int fileStart;
    int fileEnd; 
    char *keyword;
    char **argv;     
};

//function that searches for keyword
void *search(void *arg){
    struct threadArg *args = (struct threadArg *)arg;
    int amount = 0;

    printf("Thread [%d] searching %d files (%d - %d)\n", args->threadIndex, args->fileEnd - args->fileStart, args->fileStart, args->fileEnd);

    for( int i = args->fileStart; i < args->fileEnd; i++ ){
        FILE* fp = fopen(args->argv[i], "r");
        if( fp == NULL ){
            printf("Thread [%d] Error: Cannot open file\n", args->threadIndex);
            exit(0);
        } else {
            //vars for neat printing in red color :)
            char buffer[100];
            char *index;
            char *temp = buffer;

            //searching all of the file
            while(fgets(buffer, sizeof(buffer), fp) != NULL){
                if((index = strstr(buffer, args->keyword)) != NULL){
                    amount = amount + 1;
                    printf("%.*s", (int)(index-temp), temp);
                    printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, args->keyword);
                    printf("%s", index + strlen(args->keyword));
                }
            }
        }
        fclose(fp);
    }
    printf("Thread [%d] found %d lines containing keyword: %s\n", args->threadIndex, amount, args->keyword);
    int *threadReturn = malloc(sizeof(int));
    if (threadReturn == NULL) {
        printf("Malloc Error: threadReturn");
        pthread_exit(NULL);
    }
    *threadReturn = amount;
    return threadReturn;
}




int main(int argc, char* argv[]) {
    if( argc < 4 ){
        printf("usage: ./grep <NumThreads> <Keyword> <Files>\n");
        return 0;
    }

    //vars
    struct timeval start, end;
    double elapsed;

    int numThreads = atoi(argv[1]);
    int totalFile = argc - 3;
    int filePerThread = (totalFile + atoi(argv[1]) - 1) / atoi(argv[1]);
    
    //start timer
    gettimeofday(&start, NULL);

    // creating an array to hold information for each thread, to prevent race condition
    pthread_t *threads = malloc(numThreads * sizeof(pthread_t));
    struct threadArg *args = malloc(numThreads * sizeof(struct threadArg));

    //populating arrays and creating the respective threads
    for( int i = 0; i < numThreads; i++){
        args[i].threadIndex = i;
        args[i].fileStart = 3 + i * filePerThread;
        args[i].fileEnd = args[i].fileStart + filePerThread;
        if( args[i].fileEnd > argc){
            args[i].fileEnd = argc;
        }
        args[i].keyword = argv[2];
        args[i].argv = argv;

        pthread_create(&threads[i], NULL, search, &args[i]);
    }

    int totalCount = 0;

    //collecting results 
    for( int i = 0; i < numThreads; i++){
        void *returnValue;
        pthread_join(threads[i], &returnValue);
        if(returnValue != NULL){
            totalCount += *((int *)returnValue);
            free(returnValue);
        }
    }
    
    printf("Total occurances: %d\n", totalCount);
    gettimeofday(&end, NULL);
    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf("Elapsed time: %f ms\n", elapsed);

    free(threads);
    free(args);
    return 0;
}
