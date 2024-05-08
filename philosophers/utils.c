/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/08 12:50:20 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    ft_error(t_node *node, char *str)
{
    t_node *tmp;

    tmp = node;
    while (node)
    {
        tmp = node->next;
		if (node->data)
        	free(node->data);
        free(node);
        node = tmp;
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