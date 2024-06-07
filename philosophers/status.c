/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:48:05 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/07 13:13:46 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->table->die);
	philo->table->ph_dead = 1;
	pthread_mutex_unlock(philo->table->die);
}

int	ft_im_dead(t_philo *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(philo->table->die);
	status = philo->table->ph_dead;
	pthread_mutex_unlock(philo->table->die);
	return (status);
}

int	check_philo_dead(t_philo *philo)
{
	t_time			time;
	long long		starvation;

	gettimeofday(&time, NULL);
	starvation = (time.tv_sec - philo->last_eat->tv_sec) * 1000;
	starvation += (time.tv_usec - philo->last_eat->tv_usec) / 1000;
	if (starvation > philo->tt_die)
	{
		ft_msg(philo, "dead");
		return (1);
	}
	return (0);
}

void	ft_msg(t_philo *philo, char *str)
{
	long	time;
	t_time	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec - philo->time->tv_sec) * 1000;
	time += (current_time.tv_usec - philo->time->tv_usec) / 1000;
	pthread_mutex_lock(philo->table->write);
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
	if (!strncmp(str, "dead", 4))
	{
		printf("\033[0;31m%ld %d died\n", time, philo->id);
		ft_dead(philo);
	}
	pthread_mutex_unlock(philo->table->write);
}
