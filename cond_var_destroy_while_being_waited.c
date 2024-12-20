#include <stdio.h>
#include <pthread.h>
#include <errno.h>
// This test verifies that helgrind detects (and does not crash) when
// the guest application wrongly destroys a cond var being waited
// upon.
pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t thread;

void *ThreadFunction(void *ptr)
{
   pthread_mutex_lock(&mutex);
   pthread_cond_signal(&cond);
   pthread_cond_destroy(&cond); // ERROR!!!
   pthread_mutex_unlock(&mutex);
   return NULL;
}

int main()
{
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond, NULL);

   pthread_mutex_lock(&mutex);
   pthread_create(&thread, NULL, ThreadFunction, (void *)NULL);
   pthread_cond_wait(&cond, &mutex);
   pthread_mutex_unlock(&mutex);

   pthread_join(thread, NULL);
   pthread_mutex_destroy(&mutex);
   printf("finished\n");
   return 0;
}