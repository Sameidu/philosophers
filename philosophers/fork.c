/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:51:23 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/06 10:45:13 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_unlock_fork(int *fork, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*fork = 0;
	pthread_mutex_unlock(mutex);
}

int	ft_pick_fork(int *fork, pthread_mutex_t *mutex)
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
