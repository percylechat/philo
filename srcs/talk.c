#include "../includes/philo.h"

void    say_hello(t_phi *p)
{
    int ret;

    ret = pthread_mutex_lock(p->main);
    if (ret != 0)
        return;
    ft_putstr_fd("HELLO i am philo ", 1);
    ft_putstr_nbr(p->num, 1);
    ft_putstr_fd("\n", 1);
    ret = pthread_mutex_unlock(p->main);
    if (ret != 0)
        return;
}

void    say_food(t_phi *p)
{
    int ret;

    ret = pthread_mutex_lock(p->main);
    if (ret != 0)
        return;    
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num, 1);
    ft_putstr_fd(" is eating\n", 1);
    ret = pthread_mutex_unlock(p->main);
    if (ret != 0)
        return;
}

void    say_dead(t_phi *p)
{
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num, 1);
    ft_putstr_fd(" is dead\n", 1);
}

void    say_sleep(t_phi *p)
{
    int ret;

    ret = pthread_mutex_lock(p->main);
    if (ret != 0)
        return;
    ft_putstr_nbr(get_time(p), 1);
    ft_putstr_fd(" ", 1);
    ft_putstr_nbr(p->num, 1);
    ft_putstr_fd(" is sleeping\n", 1);
    ret = pthread_mutex_unlock(p->main);
    if (ret != 0)
        return;
}
