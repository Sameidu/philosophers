/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:57:56 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 21:05:31 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static void free_table(t_soft **philo, t_mutex **forks)
{
	free((*philo));
	free((*forks));
}

static int	philo_cleaner(t_soft *philo, int total)
{
	int	i;

	i = -1;
	while (++i < total)
	{
		if (pthread_join(philo[i].philo, NULL) != 0)
			return (perror("a join failed"), -1);
	}
	return (i);
}

static int	philo_creator(t_soft *philo, int total)
{
	int	i;

	i = -1;
	while (++i < total)
	{
		if (pthread_create(&philo[i].philo, NULL, routine, (void *)&philo[i]))
			return (perror("thread creation failed"), -1);
	}
	return (i);
}

static void	simulation_start(t_soft *philo, t_control *control)
{
	int	total;

	total = philo->total_philos;
	if (philo_creator(philo, total) == -1)
	{
		cleaner_of_forks(control, total);
		mind_control_check(control, 3);
	}
	if (philo_cleaner(philo, total) == -1)
	{
		cleaner_of_forks(control, total);
		mind_control_check(control, 3);
	}
	pthread_mutex_destroy(control->start_flag);
	cleaner_of_forks(control, total);
	mind_control_check(control, 4);
}

void	philosophers(int argc, char **argv)
{
	t_control	control;
	t_soft		*philo;
	t_mutex		*forks;
	t_mutex		simulation_flag;

	philo = ft_calloc(ft_atoi(argv[1]), sizeof(t_soft));
	forks = ft_calloc(ft_atoi(argv[1]), sizeof(t_soft));
	if (init_control(&control, forks) == 1)
		return ;
	init_philos(&control, philo, argv, argc);
	control.philos = philo;
	control.start_flag = &simulation_flag;
	if (init_mutexes(&control) == -1)
		return ;
	if (init_tags(&control.fork_tags, argv) == 1)
	{
		cleaner_of_forks(&control, control.philos->total_philos);
		mind_control_check(&control, 4);
		pthread_mutex_destroy(control.start_flag);
		free_the_mind(&control);
		return ;
	}
	lets_add_forks(philo, forks, control.fork_tags);
	simulation_start(philo, &control);
	free_table(&philo, &forks);
}
