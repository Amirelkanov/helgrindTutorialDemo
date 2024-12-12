
// This program checks that Helgrind reports the five degenerate
// uses of the barrier functions shown. 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

void *child1(void *arg)
{
    pthread_barrier_wait((pthread_barrier_t *)arg);
    return NULL;
}

int main(void)
{
    pthread_barrier_t *bar1, *bar2, *bar3, *bar4;
    pthread_t thr1, thr2;
    int r;

    // initialise a barrier with a zero count
    fprintf(stderr, "\ninitialise a barrier with zero count\n");
    bar1 = malloc(sizeof(pthread_barrier_t));
    pthread_barrier_init(bar1, NULL, 0);

    // initialise a barrier twice
    fprintf(stderr, "\ninitialise a barrier twice\n");
    bar2 = malloc(sizeof(pthread_barrier_t));
    pthread_barrier_init(bar2, NULL, 1);
    pthread_barrier_init(bar2, NULL, 1);

    // initialise a barrier which has threads waiting on it.
    fprintf(stderr, "\ninitialise a barrier which has threads waiting on it\n");
    bar3 = malloc(sizeof(pthread_barrier_t));
    pthread_barrier_init(bar3, NULL, 2);
    // create a thread, whose only purpose is to block on the barrier
    pthread_create(&thr1, NULL, child1, (void *)bar3);
    // guarantee that it gets there first
    sleep(1);
    // and now reinitialise
    pthread_barrier_init(bar3, NULL, 3);

    // destroy a barrier that has threads waiting at it
    fprintf(stderr, "\ndestroy a barrier that has waiting threads\n");
    // once again, create a thread, whose only purpose is to block. 
    bar4 = malloc(sizeof(pthread_barrier_t));
    pthread_barrier_init(bar4, NULL, 2);
    // create a thread, whose only purpose is to block on the barrier
    pthread_create(&thr2, NULL, child1, (void *)bar4);
    // guarantee that it gets there first
    sleep(1);
  
    // and now destroy
    pthread_barrier_destroy(bar4);
    
    return 0;
}