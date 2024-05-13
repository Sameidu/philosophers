/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:06 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/13 13:12:26 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_fork(int nb)
{
	pthread_mutex_t	*fork;
	int		i;

	fork = (pthread_mutex_t *)malloc(nb * sizeof(pthread_mutex_t));
	if (!fork)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (fork);
}

void	ft_init_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_create(&(philo[i].thread), NULL, ft_print_philo, &(philo[i]));
		i++;
	}
}

void	ft_wait_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	ft_destroy_mutex(pthread_mutex_t *fork, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}