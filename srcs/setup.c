/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 10:28:21 by budal-bi          #+#    #+#             */
/*   Updated: 2021/08/15 14:20:18 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_param(int argc, char **argv, t_info *info)
{
	info->philo = ft_atoi(argv[1]);
	info->die = ft_atoi(argv[2]);
	info->eat = ft_atoi(argv[3]);
	info->sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		info->goal = ft_atoi(argv[5]);
		if (info->goal == -1)
			return (-1);
	}
	else
		info->goal = 0;
	if (info->philo == -1 || info->die == -1 || info->eat == -1 || \
		info->sleep == -1)
		return (-1);
	if (info->philo == 0)
		return (-1);
	info->life = 0;
	info->food = 0;
	return (0);
}

int	error_arg(int num)
{
	if (num == 0)
		ft_putstr_fd("Error: arguments\n", 2);
	else if (num == 1)
		ft_putstr_fd("Error: invalid parameter\n", 2);
	return (-1);
}

void	prep_philo(t_info *info)
{
	int	i;

	i = 0;
	info->philos = (t_phi *)malloc(sizeof(t_phi) * info->philo);
	if (!info->philos)
		return ;
	while (i < info->philo)
	{
		info->philos[i].num = i;
		info->philos[i].total = info->philo;
		info->philos[i].eat_count = 0;
		info->philos[i].status = 0;
		info->philos[i].die = info->die;
		info->philos[i].eat = info->eat;
		info->philos[i].sleep = info->sleep;
		info->philos[i].goal = info->goal;
		info->philos[i].life = &info->life;
		info->philos[i].food = &info->food;
		if (i != 0)
			info->philos[i].l_spoon = &info->spoons[i - 1];
		else
			info->philos[i].l_spoon = &info->spoons[info->philo - 1];
		info->philos[i].r_spoon = &info->spoons[i];
		info->philos[i++].main = &info->main;
	}
}

void	create_spoons(t_info *info)
{
	int	i;

	i = 0;
	info->spoons = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
				info->philo);
	if (!info->spoons)
		return ;
	while (i < info->philo)
	{
		pthread_mutex_init(&info->spoons[i], NULL);
		i++;
	}
}
