/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:45:19 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/20 11:46:58 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

static int	try_acquire_forks_odds(t_soft *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if ((*philo->r_status) == 0)
	{
		(*philo->r_status) = 1;
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if ((*philo->l_status) == 0)
		{
			(*philo->l_status) = 1;
			pthread_mutex_unlock(philo->left_fork);
			return (0);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			(*philo->r_status) = 0;
			pthread_mutex_unlock(philo->right_fork);
		}
		pthread_mutex_unlock(philo->left_fork);
	}
	else
		pthread_mutex_unlock(philo->right_fork);
	return (1);
}

static int	try_acquire_forks_pairs(t_soft *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if ((*philo->l_status) == 0)
	{
		(*philo->l_status) = 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		if ((*philo->r_status) == 0)
		{
			(*philo->r_status) = 1;
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		else
		{
			pthread_mutex_lock(philo->left_fork);
			(*philo->l_status) = 0;
			pthread_mutex_unlock(philo->left_fork);
		}
		pthread_mutex_unlock(philo->right_fork);
	}
	else
		pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	can_i_grab_forks(t_soft *philo)
{
	if (philo->id % 2 == 0)
	{
		while (try_acquire_forks_pairs(philo) != 0)
			usleep(10);
	}
	else
	{
	 	while (try_acquire_forks_odds(philo) != 0)
	 		usleep(10);
	}
	return (0);
}
