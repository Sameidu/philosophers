/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:41:26 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:51:47 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

static int	init_start_flag(t_control *control, t_soft *philo)
{
	int	i;

	i = -1;
	while (++i < philo->total_philos)
	{
		if (pthread_mutex_init(control->start_flag, NULL) != 0)
			return (1);
	}
	return (-1);
}

static int	init_forks(t_control *control)
{
	int	i;

	i = -1;
	while (++i < control->philos->total_philos)
	{
		if (pthread_mutex_init(&control->forks[i], NULL) != 0)
			return (i);
	}
	return (-1);
}

static int	control_mutexes(t_control *control)
{
	if (pthread_mutex_init(control->flag, NULL) != 0)
		return (1);
	if (pthread_mutex_init(control->talk, NULL) != 0)
		return (2);
	if (pthread_mutex_init(control->meal, NULL) != 0)
		return (3);
	return (-1);
}

int	init_mutexes(t_control *control)
{
	int	checker;

	checker = control_mutexes(control);
	if (checker != -1)
	{
		mind_control_check(control, checker);
		return (free_the_mind(control), 1);
	}
	checker = init_forks(control);
	if (checker != -1)
	{
		cleaner_of_forks(control, checker);
		mind_control_check(control, 3);
		return (free_the_mind(control), 1);
	}
	checker = init_start_flag(control, control->philos);
	if (checker != -1)
	{
		cleaner_of_forks(control, control->philos->total_philos);
		mind_control_check(control, 3);
		pthread_mutex_destroy(control->start_flag);
		return (free_the_mind(control), 1);
	}
	return (0);
}
