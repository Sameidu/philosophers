#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	pthread_t	thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int	id;
	int	nb_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	tt_thing;
	int	nb_ph_eat;
	long long time;
	struct timeval	start;
}		t_philo;

// UTILS
long	ft_atol(char *str);
int		ft_isnum(int c);
int		ft_error(t_philo *node, char *str);
void	*ft_print_philo(void *node);

// LIST
t_philo	*ft_init_args(int argc, char **argv, pthread_mutex_t *forks);

// INIT
pthread_mutex_t	*ft_init_forks(int nb);
void	ft_init_threads(t_philo *philo);
void	ft_wait_threads(t_philo *philo);
void	ft_destroy_mutex(pthread_mutex_t *forks, int nb);

#endif