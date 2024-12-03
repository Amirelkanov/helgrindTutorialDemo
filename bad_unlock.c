/* Check that an error is reported for various kinds of bogus
   pthread_mutex_unlock calls. */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *child_fn(void *arg)
{
   pthread_mutex_unlock((pthread_mutex_t *)arg); /* ERROR */
   return NULL;
}


int main(void)
{
   pthread_t child;
   pthread_mutex_t mx1, mx2;

   /* Unlocking a lock that is already unlocked */
   pthread_mutex_init(&mx1, NULL);
   pthread_mutex_lock(&mx1);
   pthread_mutex_unlock(&mx1);

   pthread_mutex_unlock(&mx1); /* ERROR */

   /* Unlocking a lock that is held by a different thread */
   pthread_mutex_init(&mx2, NULL);
   pthread_mutex_lock(&mx2);
   // start child and get it to unlock this lock
   pthread_create(&child, NULL, child_fn, (void *)&mx2);
   /* child runs and attempts to unlock our lock.  Error
      is reported in child_fn. */
   pthread_join(child, NULL);
   
   return 0;
}