/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/07 13:34:39 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node	*ft_create_node(int argc, char **argv, int i)
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
    new->data->nb_philo = ft_atol(argv[1]);
    new->data->tt_die = ft_atol(argv[2]);
    new->data->tt_eat = ft_atol(argv[3]);
    new->data->tt_sleep = ft_atol(argv[4]);
    new->data->tt_thing = 0;
	if (argc == 6)
		new->data->nb_ph_eat = ft_atol(argv[5]);
	else
		new->data->nb_ph_eat = -1;
	return (new);
}

static t_node *insert_node(t_node *node, t_node *new_node)
{
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
    return (node);
}

t_node *ft_init_args(int argc, char **argv)
{
    int i;
    int nb_philo;
    t_node *new_node;
    t_node *node;

    i = 1;
    node = NULL;
    nb_philo = ft_atol(argv[1]);
    while (nb_philo > 0)
	{
        new_node = ft_create_node(argc, argv, i);
        if (new_node == NULL)
            return NULL;
        node = insert_node(node, new_node);
        if (node == NULL)
            return NULL;
        nb_philo--;
        i++;
    }
    return (node);
}
