/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/02 12:20:33 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Hacer un ft_exit para salir del programa y liberar memoria

void	ft_exit(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	ft_isnum(int c)
{
	return(c >= '0' && c <= '9');
}

int	ft_check_args(char *argv)
{
	long	aux;
	char	*num;

	num = argv;
	if (!argv)
		return (0);
	if (*argv == '-' || *argv == '+')
		argv++;
	if (*argv == '\0')
		return (0);
	while (*argv != '\0')
	{
		if (!ft_isnum(*argv))
			return (0);
		argv++;
	}
	aux = ft_atol(num);
	if (aux > INT_MAX || aux < INT_MIN)
		return (0);
	return (1);
}

long	ft_atol(char *str)
{
	long	nb;
	int		i;

	i = 0;
	nb = 0;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			printf("Error: Argument cannot be a negative number\n");
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb < INT_MIN || nb > INT_MAX)
			ft_exit("Error: Argument is not within de range of int\n");
		i++;
	}
	if (str[i] != '\0')
		printf("Error: Argument is not a valid number\n");
	return (nb);
}