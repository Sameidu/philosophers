/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:26:15 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:43:51 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

size_t	ft_atost(const char *str)
{
	int		i;
	long	result;
	char	*str1;

	str1 = (char *)str;
	i = -1;
	result = 0;
	while ((str1[i] >= 9 && str1[i] <= 13) || (str1[i] == ' '))
		i++;
	while (str1[i] >= '0' && str1[i] <= '9')
		result = result * 10 + str1[i++] - '0';
	return (result);
}
