#include <pthread.h>

int var = 0;
// pthread_mutex_t var_m = PTHREAD_MUTEX_INITIALIZER;

void *child_fn(void *arg)
{
    var++; /* Unprotected relative to parent */
    return NULL;
}

int main(void)
{
    pthread_t child;
    pthread_create(&child, NULL, child_fn, NULL);
    var++; /* Unprotected relative to child */
    pthread_join(child, NULL);
    return 0;
}