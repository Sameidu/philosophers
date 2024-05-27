/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:48:05 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/27 18:54:21 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msg(t_philo *thread, char *str)
{
	t_philo	*philo;
	long	time;

	philo = thread;
	time = ft_time() - philo->time;
	pthread_mutex_lock(philo->write);
	if (ft_im_alive(philo))
	{
		pthread_mutex_unlock(philo->write);
		return ;
	}
	if (!strncmp(str, "fork", 3))
		printf("\033[0;33m%ld %d has taken a fork\n", time, philo->id);
	if (!strncmp(str, "eat", 3))
		printf("\033[0;32m%ld %d is eating\n", time, philo->id);
	if (!strncmp(str, "sleep", 5))
		printf("\033[0;36m%ld %d is sleeping\n", time, philo->id);
	if (!strncmp(str, "think", 5))
		printf("\033[0;35m%ld %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(philo->write);
}

int	ft_im_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->die);
	if (*(philo->ph_dead) == 1)
	{
		pthread_mutex_unlock(philo->die);
		return (1);
	}
	pthread_mutex_unlock(philo->die);
	return (0);
}

void	ft_im_dead(t_philo *philo)
{
	long	time;

	time = ft_time() - philo->time;
	pthread_mutex_lock(philo->die);
	if (ft_time() - philo->last_eat > philo->tt_die)
	{
		if (*(philo->ph_dead) == 1)
		{
			pthread_mutex_unlock(philo->die);
			return ;
		}
		printf("\033[0;31m%ld %d died\n", time, philo->id);
		*(philo->ph_dead) = 1;
	}
	pthread_mutex_unlock(philo->die);
}
