#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

//thread count initialization
pthread_t tid[4];
//counter
int pplCounter;

//locking mechanism
pthread_mutex_t lock;

//after mutex initialization we make a function for people entering elevator
void* personEnters(void* arg)
{
  pthread_mutex_lock(&lock);

  unsigned long i = 0;
  pplCounter += 1;

  printf("\n Person %d has entered elevator: \n", pplCounter );
  for (i = 0; i < 4; i++)
  {
    printf("\n Person %d is in side the elevator \n", pplCounter);
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

//mutex is destroyed after the threads are done
int main(void)
{
  int i = 0;
  int test;

  while (i < 4)
  {
    test = pthread_create(&(tid[i]), NULL, &personEnters, NULL);

    if (test != 0)
    {
      printf("\n Thread cant be created! Sorry!");
    }
    i++;
  }
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_join(tid[3], NULL);
  pthread_mutex_destroy(&lock);

  return 0;
}
