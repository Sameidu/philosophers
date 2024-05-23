/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:06 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/23 12:17:18 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_forks(int nb)
{
	pthread_mutex_t	*forks;
	int		i;

	forks = (pthread_mutex_t *)malloc(nb * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	ft_init_threads(t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		pthread_create(&(philo[i].thread), NULL, ft_routine, &(philo[i]));
		i++;
	}
}

void	ft_wait_threads(t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < ft_atol(argv[1]))
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	ft_destroy_mutex(t_resources *table, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->forks);
	pthread_mutex_destroy(table->die);
	free(table->die);
	free(table);
}