/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/16 12:49:42 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_time(void)
{
	t_time init;

	gettimeofday(&init, NULL);
	return (init.tv_sec * 1000 + init.tv_usec / 1000);
}

int    ft_error(t_philo *node, char *str)
{
    while (node)
    {
		if (node)
        	free(node);
    }
    printf("%s\n", str);
    return (1);
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
		return (ft_error(NULL, "Error: Argument is empty"), -1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb < INT_MIN || nb > INT_MAX)
			return (ft_error(NULL, "Error: Argument is out of range"), -1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (nb);
}