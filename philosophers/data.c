/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/06 12:25:25 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_save_philo(t_philo *node, int i, char **argv, int argc)
{
	node[i].id = i + 1;
	node[i].tt_die = ft_atol(argv[2]);
	node[i].tt_eat = ft_atol(argv[3]);
	node[i].tt_sleep = ft_atol(argv[4]);
	node[i].tt_thing = node[i].tt_eat - node[i].tt_sleep + 2;
	node[i].f_left = 0;
	node[i].f_right = 0;
	node[i].time = malloc(sizeof(t_time));
	if (!node[i].time)
		ft_error(node, "Error: No memory for time");
	gettimeofday(node[i].time, NULL);
	node[i].last_eat = malloc(sizeof(t_time));
	if (!node[i].last_eat)
		ft_error(node, "Error: No memory for last_eat");
	gettimeofday(node[i].last_eat, NULL);
	if (argc == 6)
		node[i].nb_ph_eat = ft_atol(argv[5]);
	else
		node[i].nb_ph_eat = -1;
}

t_philo	*ft_init_philo(int argc, char **argv, t_resources *table)
{
	int		i;
	int		nb_philo;
	t_philo	*new_node;

	i = 0;
	nb_philo = ft_atol(argv[1]);
	new_node = (t_philo *)malloc(nb_philo * sizeof(t_philo));
	if (!new_node)
		return (ft_error(NULL, "Error: No memory for node"), NULL);
	while (nb_philo > 0)
	{
		ft_save_philo(new_node, i, argv, argc);
		new_node[i].table = table;
		nb_philo--;
		i++;
	}
	i = -1;
	while (++i < ft_atol(argv[1]))
	{
		new_node[i].left = &table->forks[i];
		new_node[i].right = &table->forks[(i + 1) % ft_atol(argv[1])];
		new_node[i].f_left = &table->take_fork[i];
		new_node[i].f_right = &table->take_fork[(i + 1) % ft_atol(argv[1])];
	}
	return (new_node);
}

int	*ft_id_fork(long nb)
{
	int	i;
	int	*fork;

	i = 0;
	fork = (int *)malloc(nb * sizeof(int));
	if (!fork)
		return (ft_error(NULL, "Error: No memory for id"), NULL);
	while (i < nb)
	{
		fork[i] = 0;
		i++;
	}
	return (fork);
}

t_resources	*ft_init_table(char **argv)
{	
	t_resources	*table;

	table = malloc(sizeof(t_resources));
	if (!table)
		return (ft_error(NULL, "Error: No memory for table"), NULL);
	table->die = malloc(sizeof(pthread_mutex_t));
	if (!table->die)
		return (ft_error(NULL, "Error: No memory for die"), NULL);
	pthread_mutex_init(table->die, NULL);
	table->write = malloc(sizeof(pthread_mutex_t));
	if (!table->write)
		return (ft_error(NULL, "Error: No memory for write"), NULL);
	pthread_mutex_init(table->write, NULL);
	table->forks = ft_init_forks(ft_atol(argv[1]));
	if (!table->forks)
		return (ft_error(NULL, "Error: Could not initialize forks"), NULL);
	table->take_fork = ft_id_fork(ft_atol(argv[1]));
	if (!table->take_fork)
		return (ft_error(NULL, "Error: Could not initialize forks"), NULL);
	table->ph_dead = 0;
	return (table);
}
