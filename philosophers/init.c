/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:10:06 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/07 11:36:42 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_forks(long nb)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(nb * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_mutex_destroy(&forks[i]);
			}
			ft_error(forks, "Error: Could not init mutex");
			return (NULL);
		}
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
		if (pthread_create(&(philo[i].thread), NULL, ft_routine, &(philo[i])) != 0)
		{
			while (i > 0)
			{
				i--;
				pthread_join(philo[i].thread, NULL);
			}
			ft_error(philo, "Error: Could not create thread");
			return ;
		}
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
	pthread_mutex_destroy(table->write);
	free(table->write);
	free(table);
}
