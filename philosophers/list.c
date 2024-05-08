/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:02:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/08 12:06:39 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void   ft_init_data(t_node *node, int i, char **argv)
{
    node->data->id = i;
    node->data->nb_philo = ft_atol(argv[1]);
    node->data->tt_die = ft_atol(argv[2]);
    node->data->tt_eat = ft_atol(argv[3]);
    node->data->tt_sleep = ft_atol(argv[4]);
    node->data->tt_thing = 0;
}

static t_node	*ft_create_node(int argc, char **argv, int i)
{
	t_node	*new;

	new = (t_node *)malloc(sizeof(t_node));
	if (!new)
		return (ft_error(NULL, "Error: Could not allocate memory for node"), NULL);
	new->next = NULL;
	new->prev = NULL;
	new->data = (t_philo *)malloc(sizeof(t_philo));
	if (!new->data)
	{
		free(new);
		return (ft_error(NULL, "Error: Could not allocate memory for data"), NULL);
	}
    ft_init_data(new, i, argv);
    if (new->data->tt_die < 60 || new->data->tt_eat < 60 || new->data->tt_sleep < 60)
        return (ft_error(new, "Error: Time is less than 60"), NULL);
	if (argc == 6)
		{
            new->data->nb_ph_eat = ft_atol(argv[5]);
            if (new->data->nb_ph_eat < 1)
                return (ft_error(new, "Error: Number of times to eat is less than 1"), NULL);    
        }
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
    if (nb_philo < 2 || nb_philo > 200)
        return (ft_error(node, "Error: Number of philosophers is not within the range of 2 to 200"), NULL);
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
