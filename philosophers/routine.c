/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/29 13:16:10 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (philo->f_left == 1)
		{
			philo->f_left = 0;
			pthread_mutex_unlock(philo->left);
		}
		if (philo->f_right == 1)
		{
			philo->f_right = 0;
			pthread_mutex_unlock(philo->right);
		}
	}
	else
	{
		if (philo->f_right == 1)
		{
			philo->f_right = 0;
			pthread_mutex_unlock(philo->right);
		}
		if (philo->f_left == 1)
		{
			philo->f_left = 0;
			pthread_mutex_unlock(philo->left);
		}
	}
}

void	ft_pick_first(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		philo->f_left = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		philo->f_right = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	if (philo->left == philo->right)
	{
		ft_wait_to_die(philo);
		return ;
	}
}

void	ft_pick_second(t_philo *philo)
{
	if (ft_im_alive(philo))
	{
		ft_unlock_fork(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right);
		philo->f_right = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		pthread_mutex_lock(philo->left);
		philo->f_left = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
}

int	ft_eat(t_philo *philo)
{
	ft_im_dead(philo);
	if (ft_im_alive(philo))
		return (1);
	ft_pick_first(philo);
	ft_im_dead(philo);
	ft_pick_second(philo);
	ft_im_dead(philo);
	if (!ft_im_alive(philo))
	{
		if (philo->f_left == 1 && philo->f_right == 1)
		{
			ft_msg(philo, "eat");
			philo->last_eat = ft_time();
			usleep(philo->tt_eat * 1000);
		}
		ft_unlock_fork(philo);
		return (0);
	}
	ft_unlock_fork(philo);
	return (1);
}

int	ft_sleep(t_philo *philo)
{
	ft_im_dead(philo);
	if (ft_im_alive(philo))
		return (1);
	ft_msg(philo, "sleep");
	usleep(philo->tt_sleep * 1000);
	ft_im_dead(philo);
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
		ft_im_dead(philo);
		if (ft_im_alive(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		philo->nb_ph_eat--;
	}
	return (NULL);
}
