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

   /*
    Чтобы избежать дедлока, мы можем ввести строгий порядок захвата mutex'ов.
    Один из популярных подходов — это захват вилок в фиксированном порядке:
    каждая вилка имеет уникальный номер, и философы захватывают вилки по возрастанию номера:
         long first = left < right ? left : right;
         long second = left < right ? right : left;
   */

   long first = left;
   long second = right;
   for (i = 0; i < 1000 /*arbitrary*/; i++)
   {
      /* thinking */
      pthread_mutex_lock(&table[first].fork_m);
      pthread_mutex_lock(&table[second].fork_m);
      /* eating */
      pthread_mutex_unlock(&table[first].fork_m);
      pthread_mutex_unlock(&table[second].fork_m);
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