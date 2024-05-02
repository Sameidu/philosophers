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
	t_node	*next;
	t_node	*prev;
	t_philo	*philo;
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

//UTILS
long	ft_atol(char *str);
t_node	*ft_create_node(int argc, char **argv, int i);
void	ft_exit(char *str);
void	ft_print_lst(t_node *head);
int		ft_isnum(int c);
int		ft_check_args(char *argv);

#endif