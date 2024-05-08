/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/08 12:49:19 by smeixoei         ###   ########.fr       */
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

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (ft_error(NULL, "Error: Wrong number of argument"), 1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isnum(argv[i][j]))
				return (ft_error(NULL, "Error: Argument is not a valid number"), 1);
			j++;
		}
		i++;
	}
	return (0);
}
void	leaks(void)
{
	system("leaks -q philo");
}

int main (int argc, char **argv)
{
	t_node	*philo;
	t_node	*tmp;

	atexit(leaks);
	if (ft_check_args(argc, argv) == 1)
		return (1);
	philo = ft_init_args(argc, argv);
	if (!philo)
		return (ft_error(NULL, "Error: Could not initialize arguments"), 1);
	tmp = philo;
	while (tmp->next)
	{
		pthread_create(&tmp->thread, NULL, ft_print_philo, tmp);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	tmp = philo;
	while (tmp->next)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	tmp = philo;
	while (tmp->next)
	{
		free(tmp->data);
		free(tmp);
		tmp = tmp->next;
		if (tmp == philo)
			break;
	}
	printf("All threads have finished\n");
	return (0);
}
