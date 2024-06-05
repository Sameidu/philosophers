/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:48:05 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/05 20:59:50 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msg(t_philo *thread, char *str)
{
	t_philo	*philo;
	long	time;

	philo = thread;
	time = ft_time() - philo->time;
	pthread_mutex_lock(philo->table->write);
	if (!strncmp(str, "dead", 4))
	{
		printf("\033[0;31m%ld %d died\n", time, philo->id);
		pthread_mutex_unlock(philo->table->write);
		return ;
	}
	if (ft_im_dead(philo))
	{
		pthread_mutex_unlock(philo->table->write);
		return ;
	}
	if (!strncmp(str, "fork", 4))
		printf("\033[0;33m%ld %d has taken a fork\n", time, philo->id);
	if (!strncmp(str, "eat", 3))
		printf("\033[0;32m%ld %d is eating\n", time, philo->id);
	if (!strncmp(str, "sleep", 5))
		printf("\033[0;36m%ld %d is sleeping\n", time, philo->id);
	if (!strncmp(str, "think", 5))
		printf("\033[0;35m%ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->table->write);
}

int	ft_im_dead(t_philo *philo)
{
	// long	time;

	// time = ft_time() - philo->time;
	pthread_mutex_lock(philo->table->die);
	if (philo->table->ph_dead == 1)
	{
		pthread_mutex_unlock(philo->table->die);
		return (1);
	}
	if (ft_time() - philo->last_eat > philo->tt_die)
	{
		if (philo->table->ph_dead == 1)
		{
			pthread_mutex_unlock(philo->table->die);
			return (1);
		}
		philo->table->ph_dead = 1;
		pthread_mutex_unlock(philo->table->die);
		ft_msg(philo, "dead");
		return (0);
	}
	pthread_mutex_unlock(philo->table->die);
	return (0);
}

void	ft_wait_to_die(t_philo *philo)
{
	while (1)
	{
		if (ft_im_dead(philo))
			break ;
	}
}
