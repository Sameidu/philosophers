/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:51:23 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/30 20:54:20 by smeixoei         ###   ########.fr       */
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

void	ft_pick_first(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (*(philo->f_left) == 1)
			return ;
		pthread_mutex_lock(philo->left);
		*(philo->f_left) = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		if (*(philo->f_right) == 1)
			return ;
        pthread_mutex_lock(philo->right);
		*(philo->f_right) = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
    if (philo->left == philo->right)
		ft_wait_to_die(philo);
}

void	ft_pick_second(t_philo *philo)
{
	if (ft_im_dead(philo))
	{
		ft_unlock_fork(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		if (*(philo->f_right) == 1)
			return ;
		pthread_mutex_lock(philo->right);
		*(philo->f_right) = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
	else
	{
		if (*(philo->f_left) == 1)
			return ;
		pthread_mutex_lock(philo->left);
		*(philo->f_left) = 1;
		ft_im_dead(philo);
		ft_msg(philo, "fork");
	}
}