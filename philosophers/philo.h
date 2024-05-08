#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_node t_node;
typedef struct s_philo t_philo;

typedef struct s_node
{
	pthread_t	thread;
	t_node	*next;
	t_node	*prev;
	t_philo	*data;
}			t_node;

typedef struct s_philo
{
	int	id;
	int	nb_philo;
	int	tt_die;
	int	tt_eat;
	int	tt_sleep;
	int	tt_thing;
	int	nb_ph_eat;
}		t_philo;

// UTILS
long	ft_atol(char *str);
int		ft_isnum(int c);
int		ft_error(t_node *node, char *str);

// LIST
t_node	*ft_init_args(int argc, char **argv);
#endif