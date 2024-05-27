/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/27 18:54:20 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pick_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(philo->left);
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
}

int	ft_eat(t_philo *philo)
{
	ft_im_dead(philo);
	if (ft_im_alive(philo))
		return (1);
	ft_pick_fork(philo);
	ft_im_dead(philo);
	if (ft_im_alive(philo))
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (1);
	}
	ft_msg(philo, "eat");
	usleep(philo->tt_eat * 1000);
	philo->last_eat = ft_time();
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	ft_im_dead(philo);
	if (ft_im_alive(philo))
		return (1);
	ft_msg(philo, "sleep");
	usleep(philo->tt_sleep * 1000);
	if (ft_im_alive(philo))
		return (1);
	ft_msg(philo, "think");
	return (0);
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	while (philo->nb_ph_eat != 0)
	{
		if (ft_im_alive(philo))
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
