/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/07 13:32:07 by smeixoei         ###   ########.fr       */
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

long	ft_atol(char *str)
{
	long	nb;
	int		i;

	i = 0;
	nb = 0;
	if (str[i] == '\0')
		ft_exit("Error: Argument is empty");
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb < INT_MIN || nb > INT_MAX)
			ft_exit("Error: Argument is not within de range of int");
		i++;
	}
	if (str[i] != '\0')
		printf("Error: Argument is not a valid number\n");
	return (nb);
}