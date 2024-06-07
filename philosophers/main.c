/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/07 20:49:12 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (ft_error(NULL, "Error: Wrong number of argument"));
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isnum(argv[i][j]))
				return (ft_error(NULL, "Error: Invalid number"));
			j++;
		}
		i++;
	}
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60
		|| ft_atol(argv[4]) < 60)
		return (ft_error(NULL, "Error: Time < 60 for die/eat/sleep"));
	if (argc == 6 && (ft_atol(argv[5]) < 1 || ft_atol(argv[5]) > INT_MAX))
		return (ft_error(NULL, "Error: Number of times to eat"));
	return (0);
}

// void	leaks(void)
// {
// 	system("leaks -q philo");
// }

int	main(int argc, char **argv)
{
	t_resources	*table;
	t_philo		*philo;

	// atexit(leaks);
	if (ft_check_args(argc, argv))
		return (1);
	table = ft_init_table(argv);
	if (!table)
		return (ft_error(NULL, "Error: Could not initialize table"));
	philo = ft_init_philo(argc, argv, table);
	if (!philo)
		return (ft_error(NULL, "Error: Could not initialize arguments"));
	ft_init_threads(philo, argv);
	ft_wait_threads(philo, argv);
	if (table->ph_dead == 0)
		printf("All Philos have eaten %ld times\n", ft_atol(argv[5]));
	ft_destroy_mutex(table, ft_atol(argv[1]));
	free(philo);
	return (0);
}
