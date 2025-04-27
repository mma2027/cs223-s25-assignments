// Author: Maxfield Ma
// Date: 4/24/2025
// Description: implementation of malloc and free

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct chunk {
  int size;
  int used;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc(size_t bytes) {
    if (bytes == 0) {
        return NULL;
    }
    size_t request = ((bytes + 7) / 8) * 8;
    struct chunk *current = flist;
    struct chunk *prev = NULL;

    //seraching through freelist
    while (current) {
        if (current->size >= (int)request) {
            break;
        }
        prev = current;
        current = current->next;
    }

    //if it found a suitable chunk
    if (current) {
        //deletes from flist
        if (prev) {
            prev->next = current->next;
        } else {
            flist = current->next;
        }

        //see if it is enough for the header, if it is create it
        int leftover = current->size - (int)request;
        if (leftover >= (int)sizeof(struct chunk) + 8) {
            struct chunk *newChunk = (struct chunk *)((char *)(current + 1) + request);

            newChunk->size = leftover - sizeof(struct chunk);
            newChunk->used = 0;
            newChunk->next = flist;

            flist = newChunk;
            current->size = request;
        }

        current->used = request;
        return (void *)(current + 1);
    }

    //cant find chunk big enough in flist, create a new one
    size_t total = sizeof(struct chunk) + request;
    void *mem = sbrk(total);
    if (mem == (void *)-1) {
        return NULL;
    }

    //setting new chunk information
    current = (struct chunk *)mem;
    current->size = request;
    current->used = request;
    current->next = NULL;
    return (void *)(current + 1);
}

//go through flist and remove the pointers
void free(void *ptr) {
    if (!ptr){
        return;
    }
    struct chunk *current = (struct chunk *)ptr - 1;
    current->used = 0;
    current->next = flist;
    flist = current;
}