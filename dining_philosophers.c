#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
/* Naive dining philosophers with inconsistent lock acquisition
   ordering. */

static pthread_t phil[5];
static struct
{
   pthread_mutex_t fork_m;
} table[5];

void *dine(void *arg)
{
   int i;
   long left = (long)arg;
   long right = (left + 1) % 5;
   for (i = 0; i < 1000 /*arbitrary*/; i++)
   {
      /* thinking */
      pthread_mutex_lock(&table[left].fork_m);
      pthread_mutex_lock(&table[right].fork_m);
      /* eating */
      pthread_mutex_unlock(&table[left].fork_m);
      pthread_mutex_unlock(&table[right].fork_m);
   }
   return NULL;
}

int main(void)
{
   long i;

   for (i = 0; i < 5; i++)
      pthread_mutex_init(&table[i].fork_m, NULL);

   for (i = 0; i < 5; i++)
      pthread_create(&phil[i], NULL, dine, (void *)i);

   sleep(1);

   for (i = 0; i < 5; i++)
      pthread_join(phil[i], NULL);

   return 0;
}