/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:26:32 by budal-bi          #+#    #+#             */
/*   Updated: 2021/08/15 14:58:00 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	live_life(t_phi *p)
{
	int	i;

	i = check_alive(p);
	if (i > 0)
		return ;
	else if ((p->num + 1) % 2 != 0)
	{
		get_spoons(p);
		i = check_alive(p);
		if (i > 0)
			return ;
		handle_sleep(p);
		i = check_alive(p);
		if (i > 0)
			return ;
	}
	else
	{
		handle_sleep(p);
		i = check_alive(p);
		if (i > 0)
			return ;
		get_spoons(p);
		i = check_alive(p);
		if (i > 0)
			return ;
	}
}

void	*ft_life(void *test)
{
	t_phi	*p;

	p = (t_phi *)test;
	gettimeofday(&p->born, NULL);
	gettimeofday(&p->last_meal, NULL);
	while (p->status == 0 && *p->life == 0)
	{
		live_life(p);
	}
	if (check_alive(p) == 2)
		return (NULL);
	return (NULL);
}

void	run_life(t_info *info)
{
	int	i;
	int	ret;

	i = 0;
	ft_putstr_fd("Start:\n", 1);
	while (i < info->philo)
	{
		ret = pthread_create(&info->philos[i].id, NULL, ft_life, \
			&info->philos[i]);
		if (ret == -1)
		{
			ft_putstr_fd("error thread", 2);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < info->philo)
	{
		pthread_join(info->philos[i].id, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_info	info[1];
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (error_arg(0));
	if (get_param(argc, argv, info) == -1)
		return (error_arg(1));
	pthread_mutex_init(&info->main, NULL);
	create_spoons(info);
	prep_philo(info);
	run_life(info);
	while (i < info->philo)
		pthread_mutex_destroy(&info->spoons[i++]);
	pthread_mutex_destroy(&info->main);
	free(info->philos);
	free(info->spoons);
	return (0);
}
