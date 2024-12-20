/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:40 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:51:57 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

int	init_tags(int **fork_tags, char **argv)
{
	int	i;
	int	total;

	i = -1;
	total = ft_atoi(argv[1]);
	*fork_tags = malloc(total * sizeof(int));
	if (*fork_tags == NULL)
		return (1);
	while (++i < total)
		(*fork_tags)[i] = 0;
	return (0);
}

void	lets_add_forks(t_soft *philos, t_mutex *forks, int *fork_tags)
{
	int	i;
	int	total;

	i = -1;
	total = philos[0].total_philos;
	while (++i < total)
	{
		if (i == 0)
		{
			philos[i].left_fork = &forks[total - 1];
			philos[i].l_status = &fork_tags[total - 1];
			philos[i].right_fork = &forks[i];
			philos[i].r_status = &fork_tags[i];
		}
		else
		{
			philos[i].left_fork = &forks[i - 1];
			philos[i].l_status = &fork_tags[i - 1];
			philos[i].right_fork = &forks[i];
			philos[i].r_status = &fork_tags[i];
		}
	}
}

void	init_philos(t_control *control, t_soft *philo, char **argv, int argc)
{
	int	i;
	int	number;

	i = -1;
	number = ft_atoi(argv[1]);
	while (++i < number)
	{
		philo[i].times_to_eat = -1;
		philo[i].id = i + 1;
		philo[i].total_philos = number;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].control = control;
		if (argc == 6)
			philo[i].times_to_eat = ft_atoi(argv[5]);
	}
}

int	init_control(t_control *control, t_mutex *forks)
{
	control->flag = malloc(sizeof(t_mutex));
	if (!control->flag)
		return (1);
	control->talk = malloc(sizeof(t_mutex));
	if (!control->talk)
		return (free(control->flag), 1);
	control->meal = malloc(sizeof(t_mutex));
	if (!control->meal)
		return (free(control->flag), free(control->talk), 1);
	if (pthread_mutex_init(control->talk, NULL) != 0)
		return (free_the_mind(control), 1);
	if (pthread_mutex_init(control->flag, NULL) != 0)
		return (free_the_mind(control), 1);
	if (pthread_mutex_init(control->meal, NULL) != 0)
		return (free_the_mind(control), 1);
	control->death = 0;
	control->simulation_ready = 0;
	control->forks = forks;
	return (0);
}
