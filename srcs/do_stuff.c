#include "../includes/philo.h"

void    handle_food(t_phi *p)
{
    int i;

    i = check_alive(p);
    if (i == 0)
    {
        say_food(p);
        gettimeofday(&p->last_meal, NULL);
        p->eat_count++;
        usleep(p->eat * 1000);
    }
    else if (i == 1)
        say_dead(p);
    pthread_mutex_unlock(p->l_spoon);
    pthread_mutex_unlock(p->r_spoon);
}

void    handle_sleep(t_phi *p)
{
    int i;

    i = check_alive(p);
    if (i == 0)
    {
        say_sleep(p);
        usleep(p->sleep * 1000);
        if ((i = check_alive(p)) == 0)
            say_think(p);
        else if (i == 1)
            say_dead(p);
    }
    else if (i == 1)
        say_dead(p);
}

void	*wait_for_spoons(void *p)
{
	t_phi *v;
    int i;

	v = (t_phi *)p;
	while (v->has_spoons != 2)
	{
        i = check_alive(p);
		if (i != 0)
        {
            if (i == 1)
                say_dead(p);
            pthread_mutex_unlock(v->l_spoon);
            pthread_mutex_unlock(v->r_spoon);
			return (NULL);
		}
        usleep(1);
	}
	return (NULL);
}

void    get_spoons(t_phi *p)
{
    pthread_t	thread;
    int i;

    i = check_alive(p);
    if (i == 0)
    {
            p->has_spoons = 0;
        pthread_create(&thread, NULL, wait_for_spoons, p);
        pthread_detach(thread);
        if (p->total > 1)
        {
            pthread_mutex_lock(p->r_spoon);
            say_spoon(p, 1);
            pthread_mutex_lock(p->l_spoon);
            say_spoon(p, 0);
            p->has_spoons = 2;
            handle_food(p);
        }
    }
    else if (i == 1)
        say_dead(p);
}