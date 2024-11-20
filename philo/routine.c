/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/11/20 15:21:09 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_unlock_fork(int *fork, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*fork = 0;
	pthread_mutex_unlock(mutex);
}

static int	ft_pick_fork(int *fork, pthread_mutex_t *mutex)
{
	int	status;

	status = 0;
	pthread_mutex_lock(mutex);
	if (*fork == 0)
	{
		*fork = 1;
		status = 1;
	}
	pthread_mutex_unlock(mutex);
	return (status);
}

static void	ft_eat(t_philo *philo)
{
	if (philo->f_left == philo->f_right)
		ft_msg(philo, "fork");
	while (1)
	{
		if (ft_im_dead(philo) || check_philo_dead(philo))
			break ;
		if (ft_pick_fork(philo->f_left, philo->left))
		{
			if (ft_pick_fork(philo->f_right, philo->right))
			{
				ft_msg(philo, "fork");
				ft_msg(philo, "fork");
				ft_msg(philo, "eat");
				gettimeofday(philo->last_eat, NULL);
				ft_nap(philo->tt_eat * 1000, philo);
				ft_unlock_fork(philo->f_right, philo->right);
				ft_unlock_fork(philo->f_left, philo->left);
				break ;
			}
			ft_unlock_fork(philo->f_left, philo->left);
		}
		ft_nap(500, philo);
	}
}

static int	ft_sleep(t_philo *philo)
{
	if (ft_im_dead(philo) || check_philo_dead(philo))
		return (1);
	ft_msg(philo, "sleep");
	ft_nap(philo->tt_sleep * 1000, philo);
	if (ft_im_dead(philo) || check_philo_dead(philo))
		return (1);
	ft_msg(philo, "think");
	ft_nap(philo->tt_thing * 1000, philo);
	return (0);
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	if (philo->id % 2 == 1)
		ft_nap(100, philo);
	while (philo->nb_ph_eat != 0)
	{
		if (ft_im_dead(philo) || check_philo_dead(philo))
			break ;
		ft_eat(philo);
		philo->nb_ph_eat--;
		if (ft_sleep(philo))
			break ;
	}
	return (NULL);
}
