/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 10:28:14 by budal-bi          #+#    #+#             */
/*   Updated: 2021/08/15 10:38:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_phi
{
	int				num;
	int				total;
	pthread_t		id;
	int				eat_count;
	int				status;
	pthread_mutex_t	*l_spoon;
	pthread_mutex_t	*r_spoon;
	int				has_spoons;
	int				die;
	int				eat;
	int				sleep;
	int				goal;
	int				*life;
	int				*food;
	struct timeval	last_meal;
	struct timeval	born;
	pthread_mutex_t	*main;
}t_phi;

typedef struct s_info
{
	int				philo;
	int				die;
	int				eat;
	int				sleep;
	int				goal;
	pthread_mutex_t	main;
	void			**start;
	pthread_mutex_t	*spoons;
	t_phi			*philos;
	int				life;
	int				food;
}t_info;

/*
**main
*/
int		get_time(t_phi *p);
int		check_alive(t_phi *p);

/*
**do_stuff
*/
void	handle_food(t_phi *p);
void	handle_sleep(t_phi *p);
void	*wait_for_spoons(void *p);
void	get_spoons(t_phi *p);

/*
**talk
*/
void	say_hello(t_phi *p);
void	say_food(t_phi *p);
void	say_dead(t_phi *p);
void	say_sleep(t_phi *p);
void	say_spoon(t_phi *p, int i);
void	say_think(t_phi *p);

/*
**setup
*/
int		get_param(int argc, char **argv, t_info *info);
int		error_arg(int num);
void	prep_philo(t_info *info);
void	create_spoons(t_info *info);

/*
**basic_utils
*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr_nbr(int i, int fd);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

/*
**ft_itoa
*/
char	*ft_itoa(int n);

#endif