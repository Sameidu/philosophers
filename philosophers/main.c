/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/02 20:23:22 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_print_philo(void *node)
{
	t_node	*philo;

	philo = node;
	printf("PHILO THREAD --> %d\n", philo->data->id);
	printf("next thread --> %d\n", philo->next->data->id);
	printf("prev thread --> %d\n\n", philo->prev->data->id);
	// printf("tt_die --> %d \n", philo->data->tt_die);
	// printf("tt_eat --> %d \n", philo->data->tt_eat);
	// printf("tt_sleep --> %d \n", philo->data->tt_sleep);
	// printf("nb_eats --> %d \n\n", philo->data->nb_ph_eat);
	return (NULL);
}

t_node	*ft_init_args(int argc, char **argv)
{
	int	i;
	int	nb_philo;
	t_node	*new_node;
	t_node	*node;

	i = 1;
	node = NULL;
	nb_philo = ft_atol(argv[1]);
	while (nb_philo > 0)
	{
		new_node = ft_create_node(argc, argv, i);
		if (new_node == NULL)
			return (NULL);
		pthread_create(&new_node->philo, NULL, ft_print_philo, new_node);
		if (node == NULL)
		{
			node = new_node;
			node->next = node;
			node->prev = node;
		}
		else
		{
			new_node->prev = node->prev;
			new_node->next = node;
			node->prev->next = new_node;
			node->prev = new_node;
		}
		nb_philo--;
		i++;
	}
	return (node);
}

int main (int argc, char **argv)
{
	t_node	*philo;
	int	i = 1;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong arguments\n");
		return (0);
	}
	while (argv[i])
	{
		if (!ft_check_args(argv[i]))
			ft_exit("Error: Not a number");
		i++;
	}
	philo = ft_init_args(argc, argv);
	ft_print_lst(philo);
	sleep(5);
	return (0);
}