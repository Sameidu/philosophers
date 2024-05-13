/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:39:22 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/13 21:25:55 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Tener en cuenta hacer una comprobación para ver si los tenedores están libres (como por ejemplo un booleano para ver si ha sido tomado o no)
// Hacer un mutex para la comprobación de que todos los filósofos están vivos.(Todos los filósofos vana tener acceso a esta comprobación)
// Crear una estructura para los datos compartidos entre los filósofos. (Tenedores, estado de los filósofos, etc)
// Incluir en la estructura de los filosofos timeval para poder calcular los valores de tiempo de meuerte, etc.
// Para que timeval funcione le tengo que restar el tiempo de inicio a la hora de ejecución. (inicia en 1970)
// Crear un bucle para que los filósofos coman, duerman y piensen. Donde mueran si no comen a tiempo.


void	*ft_print_philo(void *node)
{
	t_philo	*philo;

	philo = node;
	printf("PHILO THREAD --> %d\nRight fork --> %p\nLeft fork --> %p\nTime --> %ld\nTime 2 --> %ld\n\n",
	philo->id, philo->right, philo->left, philo->start.tv_sec, philo->start.tv_usec);
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

void	leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	*forks;
	t_philo	*philo;

	atexit(leaks);
	if (ft_check_args(argc, argv))
		return (1);
	forks = ft_init_forks(ft_atol(argv[1]));
	if (!forks)
		return (ft_error(NULL, "Error: Could not initialize forks"));
	philo = ft_init_args(argc, argv, forks);
	if (!philo)
		return (ft_error(NULL, "Error: Could not initialize arguments"));
	ft_init_threads(philo);
	ft_wait_threads(philo);
	ft_destroy_mutex(forks, ft_atol(argv[1]));
	free(forks);
	free(philo);
	return (0);
}
