#	ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_phi
{
    int num;
    pthread_t id;
    int eat_count;
    int status;
    pthread_mutex_t *l_spoon;
    pthread_mutex_t *r_spoon;
    int die;
    int eat;
    int sleep;
    int goal;
    struct timeval last_meal;
    struct timeval born;
    pthread_mutex_t *main;
}t_phi;

typedef struct s_info
{
    int philo;
    int die;
    int eat;
    int sleep;
    int goal;
    pthread_mutex_t main;
    void **start;
    pthread_mutex_t *spoons;
    t_phi *philos;
}   t_info;

/*
**main
*/
int get_time(t_phi *p);

/*
**talk
*/
void    say_hello(t_phi *p);
void    say_food(t_phi *p);
void    say_dead(t_phi *p);
void    say_sleep(t_phi *p);

/*
**setup
*/
int get_param(int argc, char **argv, t_info *info);
int error_arg(int num);
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
char		*ft_itoa(int n);

#endif