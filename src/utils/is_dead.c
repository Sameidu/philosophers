/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:15:07 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:47:13 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

void	status_reset(t_soft *philo)
{
	pthread_mutex_lock(philo->right_fork);
	(*philo->r_status) = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	(*philo->l_status) = 0;
	pthread_mutex_unlock(philo->left_fork);
}

int	is_philo_dead(t_control *control)
{
	pthread_mutex_lock(control->flag);
	if (control->death == 1)
	{
		pthread_mutex_unlock(control->flag);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(control->flag);
		return (0);
	}
}
