/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/02 20:21:27 by smeixoei         ###   ########.fr       */
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
	new->data = (t_philo *)malloc(sizeof(t_philo));
	if (!new->data)
	{
		free(new);
		ft_exit("Error: Could not allocate memory for data\n");
	}
	new->data->id = i;
    new->data->nb_philo = atol(argv[1]);
    new->data->tt_die = atol(argv[2]);
    new->data->tt_eat = atol(argv[3]);
    new->data->tt_sleep = atol(argv[4]);
    new->data->tt_thing = 0;
	if (argc == 6)
		new->data->nb_ph_eat = atol(argv[5]);
	else
		new->data->nb_ph_eat = -1;
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
		printf("PHILO --> %d\n", current->data->id);
		printf("next --> %d\n", current->next->data->id);
		printf("prev --> %d\n", current->prev->data->id);
		// printf("tt_die --> %d \n", current->data->tt_die);
		// printf("tt_eat --> %d \n", current->data->tt_eat);
		// printf("tt_sleep --> %d \n", current->data->tt_sleep);
		// printf("nb_eats --> %d \n\n", current->data->nb_ph_eat);
		current = current->next;
		next = next->next;
	}
	printf("PHILO --> %d\n\n", current->data->id);
	printf("next --> %d\n", current->next->data->id);
	printf("prev --> %d\n\n", current->prev->data->id);
	// printf("total --> %d\n", current->data->nb_philo);
	// printf("tt_die --> %d \n", current->data->tt_die);
	// printf("tt_eat --> %d \n", current->data->tt_eat);
	// printf("tt_sleep --> %d \n", current->data->tt_sleep);
	// printf("nb_eats --> %d \n\n", current->data->nb_ph_eat);
	return ;
}
