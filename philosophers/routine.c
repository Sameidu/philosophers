/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/05 21:17:29 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *philo)
{
	while (1)
	{
		if (ft_im_dead(philo) == 1)
			break ;
		if (ft_pick_left(philo->f_left, philo->left))
		{
			if (ft_pick_left(philo->f_right, philo->right))
			{
				ft_msg(philo, "fork");
				ft_msg(philo, "fork");
				ft_msg(philo, "eat");
				philo->last_eat = ft_time();
				usleep(philo->tt_eat * 1000);
				break ;
			}
			ft_unlock_fork(philo);
		}
		usleep(500);
	}
}

int	ft_sleep(t_philo *philo)
{
	if (ft_im_dead(philo))
		return (1);
	ft_msg(philo, "sleep");
	usleep(philo->tt_sleep * 1000);
	if (ft_im_dead(philo))
		return (1);
	ft_msg(philo, "think");
	if (philo->id % 2 == 1)
		usleep(650);
	return (0);
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	if (philo->id % 2 == 1)
		usleep(1650);
	while (philo->nb_ph_eat != 0 && !ft_im_dead(philo))
	{
		if (ft_im_dead(philo))
			break ;
		ft_eat(philo);
		if (ft_sleep(philo))
			break ;
		philo->nb_ph_eat--;
	}
	return (NULL);
}
