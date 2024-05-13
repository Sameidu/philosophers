/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/13 13:11:46 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_print_philo(void *node)
{
	t_philo	*philo;

	philo = node;
	printf("PHILO THREAD --> %d\nRight fork --> %p\nLeft fork --> %p\n\n",
	philo->id, philo->right, philo->left);
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
	if (ft_atol(argv[1]) <= 1 || ft_atol(argv[1]) > 200)
		return (ft_error(NULL, "Error: Number of philosophers is not between 1 and 200"), 1);
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		return (ft_error(NULL, "Error: Time to die, eat or sleep is less than 60"), 1);
	if (argc == 6 && (ft_atol(argv[5]) < 1 || ft_atol(argv[5]) > INT_MAX))
		return (ft_error(NULL, "Error: Number of times to eat is not between 1 and INT_MAX"), 1);
	return (0);
}

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*fork;
	t_philo	*philo;

	atexit(leaks);
	if (ft_check_args(argc, argv) == 1)
		return (1);
	fork = ft_init_fork(ft_atol(argv[1]));
	if (!fork)
		return (ft_error(NULL, "Error: Could not initialize forks"), 1);
	philo = ft_init_args(argc, argv, fork);
	if (!philo)
		return (ft_error(NULL, "Error: Could not initialize arguments"), 1);
	ft_init_threads(philo);
	ft_wait_threads(philo);
	ft_destroy_mutex(fork, ft_atol(argv[1]));
	free(fork);
	free(philo);
	return (0);
}
