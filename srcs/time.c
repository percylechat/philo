/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 14:24:11 by budal-bi          #+#    #+#             */
/*   Updated: 2021/09/20 11:42:28 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_time(t_phi *p)
{
	int				time;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time = (((long)now.tv_usec / 1000) + ((double)now.tv_sec * 1000)) - \
		(((long)p->born.tv_usec / 1000) + ((double)p->born.tv_sec * 1000));
	return (time);
}

int	check_alive(t_phi *p)
{
	struct timeval	now;
	long			result;

	gettimeofday(&now, NULL);
	result = (((long)now.tv_usec / 1000) + ((double)now.tv_sec * 1000)) - \
		(((long)p->last_meal.tv_usec / 1000) + ((double)p->last_meal.tv_sec * \
		1000));
	if (*p->life == 1)
		return (2);
	else if (result >= p->die)
	{
		p->status = 1;
		*p->life = 1;
		return (1);
	}
	return (0);
}

void	*wait_for_sleep(void *p)
{
	t_phi	*v;
	int		i;

	v = (t_phi *)p;
	while (v->has_spoons != 2)
	{
		i = check_alive(p);
		if (i != 0)
		{
			if (i == 1)
				speaker(p, " is dead\n");
			return (NULL);
		}
		usleep(1);
	}
	return (NULL);
}

void	*wait_for_spoons(void *p)
{
	t_phi	*v;
	int		i;

	v = (t_phi *)p;
	while (v->has_spoons != 2)
	{
		i = check_alive(p);
		if (i != 0)
		{
			if (i == 1)
				speaker(p, " is dead\n");
			pthread_mutex_unlock(v->l_spoon);
			pthread_mutex_unlock(v->r_spoon);
			return (NULL);
		}
		usleep(1);
	}
	return (NULL);
}
