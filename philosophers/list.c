/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/04/30 12:26:53 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_node	*ft_create_node(int argc, char **argv, int i)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		ft_exit("Error: Could not allocate memory for node\n");
	new->next = NULL;
	new->prev = NULL;
	new->philo = (t_philo *)malloc(sizeof(t_philo));
	if (!new->philo)
	{
		free(new);
		ft_exit("Error: Could not allocate memory for philo\n");
	}
	new->philo->id = i;
    new->philo->nb_philo = atol(argv[1]);
    new->philo->tt_die = atol(argv[2]);
    new->philo->tt_eat = atol(argv[3]);
    new->philo->tt_sleep = atol(argv[4]);
    new->philo->tt_thing = 0;
	if (argc == 6)
		new->philo->nb_ph_eat = atol(argv[5]);
	return (new);
}

void	ft_print_lst(t_node *philo)
{
	t_node	*current;
	t_node	*next;

	current = philo;
	next = current->next;
	while (next != philo)
	{
		printf("PHILO --> %d\n", current->philo->id);
		printf("total --> %d\n", current->philo->nb_philo);
		printf("tt_die --> %d \n", current->philo->tt_die);
		printf("tt_eat --> %d \n", current->philo->tt_eat);
		printf("tt_sleep --> %d \n", current->philo->tt_sleep);
		printf("nb_eats --> %d \n\n", current->philo->nb_ph_eat);
		current = current->next;
		next = next->next;
	}
	printf("PHILO --> %d\n", current->philo->id);
	printf("total --> %d\n", current->philo->nb_philo);
	printf("tt_die --> %d \n", current->philo->tt_die);
	printf("tt_eat --> %d \n", current->philo->tt_eat);
	printf("tt_sleep --> %d \n", current->philo->tt_sleep);
	printf("nb_eats --> %d \n\n", current->philo->nb_ph_eat);
	return ;
}
