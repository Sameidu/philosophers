/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:04:36 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/29 16:42:10 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct timeval	t_time;

typedef struct s_resources
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*die;
	pthread_mutex_t	*write;
	int				ph_dead;
}		t_resources;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_resources		*table;
	int				f_right;
	int				f_left;
	int				id;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_ph_eat;
	long			time;
	long			last_eat;
}		t_philo;

// UTILS
long			ft_atol(char *str);
int				ft_isnum(int c);
int				ft_error(t_philo *node, char *str);
void			*ft_routine(void *thread);
int				ft_time(void);
void			ft_msg(t_philo *thread, char *str);
int				ft_im_dead(t_philo *philo);
void			ft_wait_to_die(t_philo *philo);

// INIT
t_resources		*ft_init_table(char **argv);
t_philo			*ft_init_philo(int argc, char **argv, t_resources *forks);
pthread_mutex_t	*ft_init_forks(int nb);
void			ft_init_threads(t_philo *philo, char **argv);
void			ft_wait_threads(t_philo *philo, char **argv);
void			ft_destroy_mutex(t_resources *table, int nb);

#endif