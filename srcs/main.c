/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:26:32 by budal-bi          #+#    #+#             */
/*   Updated: 2021/08/05 15:27:48 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


int get_time(t_phi *p)
{
    int time;
    struct timeval now;
    
    gettimeofday(&now, NULL);
    time = (((long)now.tv_usec / 1000) + ((double)now.tv_sec * 1000)) - (((long)p->born.tv_usec / 1000) + ((double)p->born.tv_sec * 1000));
    return (time);
}

int check_alive(t_phi *p)
{
    struct timeval now;
    long result;

    gettimeofday(&now, NULL);
    result = (((long)now.tv_usec / 1000) + ((double)now.tv_sec * 1000)) - (((long)p->last_meal.tv_usec / 1000) + ((double)p->last_meal.tv_sec * 1000));
    // printf("time: %ld", result);
    if (result >= p->die)
        return (1);
    return (0);
}

void    handle_food(t_phi *p)
{
    if (check_alive(p) == 0)
    {
        say_food(p);
        usleep(p->eat);
        p->eat_count++;
        gettimeofday(&p->last_meal, NULL);
    }
    else
        say_dead(p);
    pthread_mutex_unlock(p->l_spoon);
    pthread_mutex_unlock(p->r_spoon);

}

void    handle_sleep(t_phi *p)
{
    write(1, "ok", 2);
    if (check_alive(p) == 0)
    {
        say_sleep(p);
        usleep(p->sleep);
    }
    else
        say_dead(p);
}

void *ft_life(void *test)
{
    t_phi *p;

    p = (t_phi *) test;
    gettimeofday(&p->born, NULL);
    gettimeofday(&p->last_meal, NULL);
    say_hello(p);
    while (p->status == 0)
    {
        if (pthread_mutex_lock(p->l_spoon) == 0 && pthread_mutex_lock(p->r_spoon) == 0 && p->num > 1)
            handle_food(p);
        handle_sleep(p);
        // handle_think(p);
    }
    say_dead(p);
    return (NULL);
}

void run_life(t_info *info)
{
    int i;
    int ret;

    i = 0;
    ft_putstr_fd("Start:\n", 1);
    while (i < info->philo)
    {
        ret = pthread_create(&info->philos[i].id, NULL, ft_life, &info->philos[i]);
        if (ret == -1)
        {
            ft_putstr_fd("error thread", 2);
            return;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_info info[1];

    if (argc < 5 || argc > 6)
        return (error_arg(0));
    if (get_param(argc, argv, info) == -1)
        return (error_arg(1));
    pthread_mutex_init(&info->main, NULL);
    create_spoons(info);
    prep_philo(info);
    run_life(info);
    return (0);
}