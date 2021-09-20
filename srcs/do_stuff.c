/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 10:27:51 by budal-bi          #+#    #+#             */
/*   Updated: 2021/09/20 11:41:27 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	speaker(t_phi *p, char *str)
{
	pthread_mutex_lock(p->main);
	ft_putstr_nbr(get_time(p), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_nbr(p->num + 1, 1);
	ft_putstr_fd(str, 1);
	pthread_mutex_unlock(p->main);
}

void	handle_food(t_phi *p)
{
	int	i;

	i = check_alive(p);
	if (i == 0)
	{
		speaker(p, " is eating\n");
		gettimeofday(&p->last_meal, NULL);
		p->eat_count++;
		if (p->eat_count == p->goal)
		{
			*p->food += 1;
			speaker(p, " is full\n");
		}
		if (*p->food == p->total)
			*p->life = 1;
		usleep(p->eat * 1000);
		// int i = 0;
		// while (i < p->eat * 1000)
		// {
		// 	usleep(1);
		// 	i++;
		// }
	}
	else if (i == 1)
		speaker(p, " is dead\n");
	pthread_mutex_unlock(p->l_spoon);
	pthread_mutex_unlock(p->r_spoon);
}

void	handle_sleep(t_phi *p)
{
	int			i;
	pthread_t	thread;

	i = check_alive(p);
	if (i == 0)
	{
		p->has_spoons = 0;
		pthread_create(&thread, NULL, wait_for_sleep, p);
		pthread_detach(thread);
		speaker(p, " is sleeping\n");
		// usleep(p->sleep * 1000);
		// int i = 0;
		// while (i < p->sleep * 1000)
		// {
		// 	usleep(1);
		// 	i++;
		// }
		p->has_spoons = 2;
		i = check_alive(p);
		if (i == 0)
			speaker(p, " is thinking\n");
		else if (i == 1)
			speaker(p, " is dead\n");
	}
	else if (i == 1)
		speaker(p, " is dead\n");
}

void	get_spoons(t_phi *p)
{
	pthread_t	thread;
	int			i;

	i = check_alive(p);
	if (i == 0)
	{
		p->has_spoons = 0;
		pthread_create(&thread, NULL, wait_for_spoons, p);
		pthread_detach(thread);
		if (p->total > 1)
		{
			pthread_mutex_lock(p->r_spoon);
			speaker(p, " has taken the spoon to his right\n");
			pthread_mutex_lock(p->l_spoon);
			speaker(p, " has taken the spoon to his left\n");
			p->has_spoons = 2;
			handle_food(p);
		}
	}
	else if (i == 1)
		speaker(p, " is dead\n");
}
