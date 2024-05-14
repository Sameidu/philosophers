/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/14 20:38:49 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_save_philo(t_philo *node, int i, char **argv, int argc)
{
    node[i].id = i + 1;
    node[i].nb_philo = ft_atol(argv[1]);
    node[i].tt_die = ft_atol(argv[2]);
    node[i].tt_eat = ft_atol(argv[3]);
    node[i].tt_sleep = ft_atol(argv[4]);
    node[i].tt_thing = 0;
    node[i].time = 0;
    gettimeofday(&node[i].start, NULL);
	if (argc == 6)
        node[i].nb_ph_eat = ft_atol(argv[5]);
	else
		node[i].nb_ph_eat = -1;
}

t_philo *ft_init_philo(int argc, char **argv, t_resources *forks)
{
    int i;
    int nb_philo;
    t_philo *new_node;

    i = 0;
    nb_philo = ft_atol(argv[1]);
    new_node = (t_philo *)malloc(nb_philo * sizeof(t_philo));
    if (!new_node)
        return (ft_error(NULL, "Error: Could not allocate memory for node"), NULL);
    while (nb_philo > 0)
	{
        ft_save_philo(new_node, i, argv, argc);
        new_node[i].die = forks->die;
        nb_philo--;
        i++;
    }
    i = 0;
    while (i < ft_atol(argv[1]))
    {
        new_node[i].left = &forks->forks[i];
        new_node[i].right = &forks->forks[(i + 1) % ft_atol(argv[1])];
        i++;
    }
    return (new_node);
}

t_resources	*ft_init_table(char **argv)
{	
	t_resources	*table;
	
	table = malloc(sizeof(t_resources));
	if (!table)
		return (ft_error(NULL, "Error: Could not allocate memory for table"), NULL);
	table->die = malloc(sizeof(pthread_mutex_t));
	if (!table->die)
		return (ft_error(NULL, "Error: Could not allocate memory for die"), NULL);
	table->forks = ft_init_forks(ft_atol(argv[1]));
	pthread_mutex_init(table->die, NULL);
	if (!table->forks)
		return (ft_error(NULL, "Error: Could not initialize forks"), NULL);
	return (table);
}
