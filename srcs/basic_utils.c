/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 22:01:51 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/14 12:07:02 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int				i;

	i = 0;
	if (!s || !fd)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putstr_nbr(int i, int fd)
{
	int		j;
	char	*buf;

	j = 0;
	buf = ft_itoa(i);
	while (buf[j])
	{
		write(fd, &buf[j], 1);
		j++;
	}
	free(buf);
}

int		ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			k;

	i = 0;
	k = 0;
	if (ft_isdigit(str[0]) == 0)
		return -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		k *= 10;
	    k += str[i] - 48;
		i++;
	}
	return (k);
}