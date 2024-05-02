/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/02 12:20:20 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

	if ((argc < 5 || argc > 6))
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
	return (0);
}