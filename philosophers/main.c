/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/07 13:35:57 by smeixoei         ###   ########.fr       */
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
	return (NULL);
}

void	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		ft_exit("Error: Wrong number of arguments");
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isnum(argv[i][j]))
				ft_exit("Error: Arguments must be only unsigned numbers");
			j++;
		}
		i++;
	}
}

int main (int argc, char **argv)
{
	t_node	*philo;
	t_node	*tmp;

	ft_check_args(argc, argv);
	philo = ft_init_args(argc, argv);
	tmp = philo;
	while (tmp->next)
	{
		pthread_create(&tmp->philo, NULL, ft_print_philo, tmp);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	tmp = philo;
	while (tmp->next)
	{
		pthread_join(tmp->philo, NULL);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	return (0);
}
