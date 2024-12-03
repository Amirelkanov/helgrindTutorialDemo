#include <pthread.h>

int var = 0;
/* pthread_mutex_t var_m;
pthread_cond_t var_cv; */

void *child_fn(void *arg)
{
    /*  pthread_mutex_lock(&var_m);
     pthread_cond_wait(&var_cv, &var_m);
     pthread_mutex_unlock(&var_m); */
    var++; /* Unprotected relative to parent */
    return NULL;
}

int main(void)
{
    pthread_t child;
    /*  pthread_mutex_init(&var_m, NULL);
     pthread_cond_init(&var_cv, NULL); */
    pthread_create(&child, NULL, child_fn, NULL);
    var++; /* Unprotected relative to child */

    /*  pthread_mutex_lock(&var_m);
     pthread_cond_signal(&var_cv);
     pthread_mutex_unlock(&var_m); */
    pthread_join(child, NULL);

    return 0;
}
