/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:51:23 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/05 21:13:06 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (*(philo->f_left) == 1)
		{
			*(philo->f_left) = 0;
			pthread_mutex_unlock(philo->left);
		}
		if (*(philo->f_right) == 1)
		{
			*(philo->f_right) = 0;
			pthread_mutex_unlock(philo->right);
		}
	}
	else
	{
		if (*(philo->f_right) == 1)
		{
			*(philo->f_right) = 0;
			pthread_mutex_unlock(philo->right);
		}
		if (*(philo->f_left) == 1)
		{
			*(philo->f_left) = 0;
			pthread_mutex_unlock(philo->left);
		}
	}
}

int	ft_pick_left(int *fork, pthread_mutex_t *mutex)
{
	int	status;

	status = 0;
	pthread_mutex_lock(mutex);
	if (fork == 0)
	{
		*(fork) = 1;
		status = 1;
	}
	pthread_mutex_unlock(mutex);
	return (status);
}

int	ft_pick_right(int *fork, pthread_mutex_t *mutex)
{
	int	status;

	status = 0;
	pthread_mutex_lock(mutex);
	if (fork == 0)
	{
		*(fork) = 1;
		status = 1;
	}
	pthread_mutex_unlock(mutex);
	return (status);
}