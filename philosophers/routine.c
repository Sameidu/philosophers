/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/23 13:14:28 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_im_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->die);
	if (ft_time() - philo->time > philo->tt_die)
	{
		if (*(philo->ph_dead) == 1)
		{
			pthread_mutex_unlock(philo->die);
			return ;
		}
		printf("Philosopher %d died\n", philo->id);
		*(philo->ph_dead) = 1;
	}
	pthread_mutex_unlock(philo->die);
}

int	ft_eat(t_philo *philo)
{
	ft_im_dead(philo);
	if (*(philo->ph_dead) == 1)
		return (1);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
	}
	else
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->left);
	}
	ft_im_dead(philo);
	if (*(philo->ph_dead) == 1)
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	printf("%ld %d is eating\n", ft_time() - philo->time, philo->id);
	usleep(philo->tt_eat * 1000);
	philo->time = ft_time();
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_im_dead(philo);
	if (*(philo->ph_dead) == 1)
		return (1);
	printf("%ld %d is sleeping\n", ft_time() - philo->time, philo->id);
	usleep(philo->tt_sleep * 1000);
	if (*(philo->ph_dead) == 1)
		return (1);
	printf("%ld %d is thinking\n", ft_time() - philo->time, philo->id);
	return (0);
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	while (philo->nb_ph_eat != 0)
	{
		if (*(philo->ph_dead) == 1)
			break ;
		ft_im_dead(philo);
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		philo->nb_ph_eat--;
	}
	return (NULL);
}
