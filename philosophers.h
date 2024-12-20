/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:32:30 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:59:59 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "./lib/libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define RST "\033[0"     // reset to default color
# define RED "\033[1;31m" // bold red
# define C "\033[1;36m"   // Bold cyan
# define G "\033[1;32m"   // bold green
# define Y "\033[1;33m"   // bold yellow
# define B "\033[1;34m"   // bold Blue
# define M "\033[1;35m"   // bold magenta
# define W "\033[1;37m"   // bold white

typedef struct s_control	t_control;
typedef pthread_mutex_t		t_mutex;

typedef struct s_soft
{
	pthread_t				philo;
	int						id;
	int						total_philos;
	int						time_to_sleep;
	int						times_to_eat;
	int						time_to_eat;
	int						*r_status;
	int						*l_status;
	size_t					time_to_die;
	size_t					start_time;
	size_t					last_meal;
	t_mutex					*right_fork;
	t_mutex					*left_fork;
	t_control				*control;
}							t_soft;

typedef struct s_control
{
	int						death;
	int						*fork_tags;
	int						simulation_ready;
	t_soft					*philos;
	t_mutex					*talk;
	t_mutex					*flag;
	t_mutex					*forks;
	t_mutex					*meal;
	t_mutex					*start_flag;
}							t_control;

// main function
void						philosophers(int argc, char **argv);

// errors
int							param_error(int i);

// parsing
int							args_parser(char **argv);
void						lets_add_forks(t_soft *philos, t_mutex *forks,
								int *fork_tags);
void						init_philos(t_control *control, t_soft *philo,
								char **argv, int argc);
void						free_the_mind(t_control *control);
int							init_tags(int **fork_tags, char **argv);
int							init_control(t_control *control, t_mutex *forks);

// utils
void						*routine(void *pointer);
void						check_health(t_soft *philo);
void						philosophers_assemble(t_soft *philo);
void						status_reset(t_soft *philo);
int							init_mutexes(t_control *control);
int							is_philo_dead(t_control *control);
int							cleaner_of_forks(t_control *control, int order);
int							ft_usleep(size_t miliseconds, t_soft *philo);
int							mind_control_check(t_control *control, int order);
int							can_i_grab_forks(t_soft *philo);
long						ft_atol(const char *str);
size_t						get_current_time(void);
#endif