/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/14 20:38:35 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Ya sólo me falta crear la rutina, lo que me da miedn hacer.
// Sé que tengo que gestionar los hilos para que solo la mitad coja uno de los tenedores al comienzo del programa.
// Pero sin usar la guarrada del usleep, se deberá poder hacer diciendo que sólo los hilos con ID par, por ejemlo
// cogen el tenedor derecho primero y los impares no hacen nada hasta que termine esta acción.
// Luego ya todos comparten la misma rutina... Es en el momento de inicio de esta.

// Ah! Y mi código, por alguna razón, tiene comportamientos indefinidos al usar fsanitize=address. 
// He descubierto que es por el ordenador del trabajo o por el SO. En el portatil furula bien.
// En el trabajo no me deja usar fsanitize=thread, como aviso a la Sara despistada.

void	*ft_print_philo(void *node)
{
	t_philo	*philo;
	long	time;

	philo = node;
	time = ft_time(philo);
	printf("PHILO THREAD --> %d\nRight fork --> %p\nLeft fork --> %p\nDie --> %p\nTime --> %ld\n\n",
	philo->id, philo->right, philo->left, philo->die, time);
	return (NULL);
}

int	ft_check_args(int argc, char **argv)
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
				return (ft_error(NULL, "Error: Argument is not a valid number"));
			j++;
		}
		i++;
	}
	if (ft_atol(argv[1]) <= 1 || ft_atol(argv[1]) > 200)
		return (ft_error(NULL, "Error: Number of philoz is not between 1 and 200"));
	if (ft_atol(argv[2]) < 60 || ft_atol(argv[3]) < 60 || ft_atol(argv[4]) < 60)
		return (ft_error(NULL, "Error: Time to die, eat or sleep is less than 60"));
	if (argc == 6 && (ft_atol(argv[5]) < 1 || ft_atol(argv[5]) > INT_MAX))
		return (ft_error(NULL, "Error: Number of times to eat is not between 1 and INT_MAX"));
	return (0);
}

// void	leaks(void)
// {
// 	system("leaks -q philo");
// }

int	main(int argc, char **argv)
{
	t_resources	*table;
	t_philo	*philo;

	// atexit(leaks);
	if (ft_check_args(argc, argv))
		return (1);
	table = ft_init_table(argv);
	if (!table)
		return (ft_error(NULL, "Error: Could not initialize table"));
	philo = ft_init_philo(argc, argv, table);
	if (!philo)
		return (ft_error(NULL, "Error: Could not initialize arguments"));
	ft_init_threads(philo);
	ft_wait_threads(philo);
	ft_destroy_mutex(table, ft_atol(argv[1]));
	free(philo);
	return (0);
}
