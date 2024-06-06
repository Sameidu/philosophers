/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/06 13:11:01 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
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
				ft_usleep(philo->tt_eat * 1000, philo);
				ft_unlock_fork(philo->f_right, philo->right);
				ft_unlock_fork(philo->f_left, philo->left);
				break ;
			}
			ft_unlock_fork(philo->f_left, philo->left);
		}
		ft_usleep(500, philo);
	}
}

void	ft_sleep(t_philo *philo)
{
	ft_msg(philo, "sleep");
	ft_usleep(philo->tt_sleep * 1000, philo);
	return ;
}

void	ft_think(t_philo *philo)
{
	ft_msg(philo, "think");
	ft_usleep(philo->tt_thing * 1000, philo);
	return ;
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	if (philo->id % 2 == 1)
		ft_usleep(100, philo);
	while (philo->nb_ph_eat != 0)
	{
		if (ft_im_dead(philo) || check_philo_dead(philo))
			break ;
		ft_eat(philo);
		if (ft_im_dead(philo) || check_philo_dead(philo))
			break ;
		ft_sleep(philo);
		if (ft_im_dead(philo) || check_philo_dead(philo))
			break ;
		ft_think(philo);
		philo->nb_ph_eat--;
	}
	return (NULL);
}
