/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:39 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/03 14:02:10 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_eat(t_philo *philo)
{
	if (ft_im_dead(philo))
		return (1);
	ft_pick_first(philo);
	ft_im_dead(philo);
	ft_pick_second(philo);
	if (!ft_im_dead(philo))
	{
		if (*(philo->f_left) == 1 && *(philo->f_right) == 1)
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
	if (ft_im_dead(philo))
		return (1);
	ft_msg(philo, "sleep");
	usleep(philo->tt_sleep * 1000);
	if (ft_im_dead(philo))
		return (1);
	ft_msg(philo, "think");
	if (philo->id % 2 == 1)
		usleep(750);
	return (0);
}

void	*ft_routine(void *thread)
{
	t_philo	*philo;

	philo = thread;
	while (philo->nb_ph_eat != 0)
	{
		if (ft_im_dead(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		philo->nb_ph_eat--;
	}
	return (NULL);
}
