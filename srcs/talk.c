#include "../includes/philo.h"

// PB DE LOCK pas meme adresse, chack cmt theo

void    say_hello(t_phi *p)
{
    pthread_mutex_lock(p->main);
    ft_putstr_fd("HELLO i am philo ", 1);
    ft_putstr_nbr(p->num + 1, 1);
    ft_putstr_fd("\n", 1);
    pthread_mutex_unlock(p->main);
}

void    say_food(t_phi *p)
{
    pthread_mutex_lock(p->main);
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num + 1, 1);
    ft_putstr_fd(" is eating\n", 1);
    pthread_mutex_unlock(p->main);
}

void    say_dead(t_phi *p)
{
    pthread_mutex_lock(p->main);
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num + 1, 1);
    ft_putstr_fd(" is dead\n", 1);
    pthread_mutex_unlock(p->main);
}

void    say_think(t_phi *p)
{
    pthread_mutex_lock(p->main);
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num + 1, 1);
    ft_putstr_fd(" is thinking\n", 1);
    pthread_mutex_unlock(p->main);
}

void    say_sleep(t_phi *p)
{
    pthread_mutex_lock(p->main);
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num + 1, 1);
    ft_putstr_fd(" is sleeping\n", 1);
    pthread_mutex_unlock(p->main);
}

void    say_spoon(t_phi *p, int i)
{
    if (i == 0)
    {
        pthread_mutex_lock(p->main);
        ft_putstr_nbr(get_time(p), 1);
        ft_putstr_fd(" ", 1);
        ft_putstr_nbr(p->num + 1, 1);
        ft_putstr_fd(" has taken the fork to his left\n", 1);
        pthread_mutex_unlock(p->main);
    }
    else
    {
        pthread_mutex_lock(p->main);
        ft_putstr_nbr(get_time(p), 1);
        ft_putstr_fd(" ", 1);
        ft_putstr_nbr(p->num + 1, 1);
        ft_putstr_fd(" has taken the fork to his right\n", 1);
        pthread_mutex_unlock(p->main);
    }
}