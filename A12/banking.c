// Author : Maxfield Ma
// Date : 4/18/2025
// Description : Using mutex and cond to transfer funds between accounts
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>

struct account {
  float balance;
  pthread_mutex_t lock;
  pthread_cond_t    cond;
};

struct thread_data {
  struct account* fromAccount;
  struct account* toAccount;
  float amount;
};

void *Transfer(void *args){
  struct thread_data* data = (struct thread_data*) args;
  struct account* fromAcct = data->fromAccount; 
  struct account* toAcct = data->toAccount; 
  float amt = data->amount;

  for (int i = 0; i < 1000; i++) {
    //waits while the bank account has funds
    pthread_mutex_lock(&fromAcct->lock);
    while (fromAcct->balance < amt) {
        pthread_cond_wait(&fromAcct->cond, &fromAcct->lock);
    }
    pthread_mutex_unlock(&fromAcct->lock);

    //looking for the earlier pointer
    struct account *first;
    struct account *second;

    if (fromAcct < toAcct) {
        first  = fromAcct;
        second = toAcct;
    } else {
        first  = toAcct;
        second = fromAcct;
    }

    //locking the earlier pointer first
    pthread_mutex_lock(&first->lock);
    pthread_mutex_lock(&second->lock);
    
    assert(fromAcct->balance >= 0);

    fromAcct->balance -= amt;
    toAcct->balance   += amt;

    //alerting that the balance in bank account grew
    pthread_cond_signal(&toAcct->cond);

    pthread_mutex_unlock(&second->lock);
    pthread_mutex_unlock(&first->lock);
  }

  return NULL;
}

int main() {
    struct account A, B;
    A.balance = 5000;
    B.balance = 5000;
    pthread_mutex_init(&A.lock, NULL);
    pthread_cond_init (&A.cond, NULL);
    pthread_mutex_init(&B.lock, NULL);
    pthread_cond_init (&B.cond, NULL);

    printf("Starting balance A: %.2f\n", A.balance);
    printf("Starting balance B: %.2f\n", B.balance);

    struct thread_data dataA;
    dataA.fromAccount = &B;
    dataA.toAccount = &A;
    dataA.amount = 1000;

    struct thread_data dataB;
    dataB.fromAccount = &A;
    dataB.toAccount = &B;
    dataB.amount = 1000;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, Transfer, &dataA);
    pthread_create(&thread2, NULL, Transfer, &dataB);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Should be the same because we transfer the same amount between both
    printf("Ending balance A: %.2f\n", A.balance);
    printf("Ending balance B: %.2f\n", B.balance);

    pthread_cond_destroy(&A.cond);
    pthread_mutex_destroy(&A.lock);
    pthread_cond_destroy(&B.cond);
    pthread_mutex_destroy(&B.lock);
    return 0;
}

