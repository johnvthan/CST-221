//Johnathan Hampton 
//CST 221 TOPIC 2
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>

//setting max
#define MAX_DEPOSITS 1000000

//variables
int balance = 0;
int depositAmt = 1;

//mutex
sem_t* mutex;

//deposit function -- void
void *deposit(void *a)
{
  int x, tmp;

  for (x = 0; x < MAX_DEPOSITS; ++x)
  {
    sem_wait(mutex);

    tmp = balance;
    tmp = tmp + depositAmt;
    balance = tmp;


    sem_post(mutex);
  }
  return NULL;
}

//creation of threads and opening the mutex
int main()
{
  pthread_t tid1, tid2;

  mutex = sem_open("Mutex", O_CREAT, 00644, 1);

  if (mutex == SEM_FAILED)
  {
    printf("\n Error creating mutex");
    exit(1);
  }

  if (pthread_create(&tid1, NULL, deposit, NULL))
  {
    printf("\n Error creating deposit thread");
    exit(1);
  }

  if (pthread_create(&tid2, NULL, deposit, NULL))
  {
    printf("\n Error creating deposit thread");
    exit(1);
  }

  if (pthread_join(tid1, NULL))
  {
    printf("\n Error joining deposit thread");
    exit(1);
  }

  if (pthread_join(tid2, NULL))
  {
    printf("\n Error joining deposit thread");
    exit(1);
  }

  if (balance < 2 * MAX_DEPOSITS)
  {
    printf("\n Bad Balance: $%d and shouldve been $%d\n", balance, 2 * MAX_DEPOSITS);
  }
  else
  {
    printf("\n Good Balance: $%d\n", balance);

    //always good to close and exit
    sem_close(mutex);
    pthread_exit(NULL);
  }


}
