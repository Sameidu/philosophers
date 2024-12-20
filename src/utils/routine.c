/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 00:40:13 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:46:52 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

static void	print_message(char *str, t_soft *philo, int flag)
{
	size_t	time;

	pthread_mutex_lock(philo->control->talk);
	time = get_current_time() - philo->start_time;
	pthread_mutex_unlock(philo->control->talk);
	if (!is_philo_dead(philo->control) && flag == 0)
		printf("%zu %d %s\n", time, philo->id, str);
	if (!is_philo_dead(philo->control) && flag == 1)
	{
		printf("%zu %d has taken a fork\n", time, philo->id);
		printf("%zu %d has taken a fork\n", time, philo->id);
		printf("%zu %d has eaten\n", time, philo->id);
	}
}

static void	lets_sleep(t_soft *philo)
{
	print_message("is sleeping", philo, 0);
	ft_usleep(philo->time_to_sleep, philo);
}

static void	lets_think(t_soft *philo)
{
	check_health(philo);
	print_message("is thinking", philo, 0);
}

static void	lets_eat(t_soft *philo)
{
	while (can_i_grab_forks(philo))
		;
	if (!is_philo_dead(philo->control))
	{
		check_health(philo);
		print_message("eating", philo, 1);
		pthread_mutex_lock(philo->control->flag);
		philo->last_meal = get_current_time();
		pthread_mutex_unlock(philo->control->flag);
		pthread_mutex_lock(philo->control->meal);
		if (philo->times_to_eat > 0)
			philo->times_to_eat--;
		pthread_mutex_unlock(philo->control->meal);
		ft_usleep(philo->time_to_eat, philo);
	}
	status_reset(philo);
}

void	*routine(void *pointer)
{
	t_soft	*philo;

	philo = pointer;
	philosophers_assemble(philo);
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	while (1)
	{
		lets_eat(philo);
		lets_think(philo);
		lets_sleep(philo);
		if (philo->times_to_eat == 0 || is_philo_dead(philo->control))
			break ;
	}
	return (0);
}
