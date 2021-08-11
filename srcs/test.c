/* Dining Philosophers */
#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#define NPHI 5
#define LEFT(k) (((k)+(NPHI-1))%NPHI)
#define RIGHT(k) (((k)+1)%NPHI)

enum e_state {THINKING,EATING,HUNGRY};

typedef struct s_table *table;
struct s_table {
    enum e_state states[NPHI];
    pthread_cond_t can_eat[NPHI];
    pthread_mutex_t *lock;
};

struct s_thparams {
    table table;
    pthread_barrier_t *sync;
    int id;
};

/* return 1 after receiving SIGINT */
int is_done(int yes)
{
    static pthread_spinlock_t *lock=NULL;
    static int done=0;
    if (!lock)
    {
        lock=malloc(sizeof(pthread_spinlock_t));
        pthread_spin_init(lock, PTHREAD_PROCESS_PRIVATE);
    }
    pthread_spin_lock(lock);
    if (yes)
        done = yes;
    pthread_spin_unlock(lock);
    return done;
}

/* where all the magic is ! */
/* test if we are hungry and */
/* our neighbors do no eat */

void test(table t, int k)
{
    if (t->states[k] == HUNGRY && t->states[LEFT(k)] != EATING && t->states[RIGHT(k)] != EATING)
    {
        t->states[k] = EATING;
        pthread_cond_signal(&(t->can_eat[k]));
    }
}

void pick(table t, int i)
{
    pthread_mutex_lock(t->lock);
    t->states[i] = HUNGRY;
    printf("Philosopher %d: hungry\n",i);
    test(t,i);
    while (t->states[i] != EATING)
        pthread_cond_wait(&t->can_eat[i], t->lock);
    printf("Philosopher %d: eating\n",i);
    pthread_mutex_unlock(t->lock);
}

void put(table t, int i)
{
    pthread_mutex_lock(t->lock);
    t->states[i] = THINKING;
    printf("Philosopher %d: thinking\n",i);
    test(t,LEFT(i));
    test(t,RIGHT(i));
    pthread_mutex_unlock(t->lock);
}

void thinking()
{
    struct timespec reg;
    reg.tv_sec = random()%6;
    reg.tv_nsec = 1000000*(random()%1000);
    if (nanosleep(&reg,NULL) == -1)
    {
        if (errno != EINTR || is_done(0))
            pthread_exit(NULL);
    }
}

void eating()
{
    struct timespec reg;
    reg.tv_sec = random()%2;
    reg.tv_nsec = 1000000*(random()%1000);
    nanosleep(&reg,NULL);
}

void *philosopher(void *ptr)
{
    struct s_thparams *p;
    p = ptr;
    pthread_barrier_wait(p->sync);
    printf("Philosopher %d:thinking\n",p->id);
    while (!is_done(0))
    {
        thinking();
        pick(p->table, p->id);
        eating();
        put(p->table, p->id);
    }
    pthread_exit(NULL);
}

void handle_int(int sig)
{
    is_done(1);
    signal(sig,handle_int);
}

int main(int argc, char *argv[])
{
    table t;
    struct s_thparams *p;
    pthread_t th[NPHI];
    pthread_mutex_t lock;
    pthread_barrier_t sync;
    size_t i, seed=42;
    signal(SIGINT, handle_int);

    if (argc>1)
        seed = atoi(argv[1]);
    srandom(seed);
    t = malloc(sizeof (struct s_table));
    pthread_barrier_init(&sync,NULL,NPHI);
    pthread_mutex_init(&lock,NULL);
    t->lock = &lock;
    for (i=0; i<NPHI; ++i)
    {
        t->states[i] = THINKING;
        pthread_cond_init(&t->can_eat[i],NULL);
    }
    for (i=0; i<NPHI; ++i)
    {
        p = malloc(sizeof (struct s_thparams));
        p->table = t;
        p->sync = &sync;
        p->id = i;
        pthread_create(th+i,NULL,philosopher,p);
    }
    for (i=0; i<NPHI; ++i)
        pthread_join(th[i], NULL);
    return 0;
}