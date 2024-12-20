/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:37:50 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:52:38 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

static int	ft_is_plus(char character)
{
	if (character == '+')
		return (1);
	return (0);
}

static int	check_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0' || str[i] > '9') && !ft_is_plus(str[i]) && i == 0)
			return (param_error(i));
		if (str[i] < '0' || str[i] > '9')
			return (param_error(i));
	}
	return (-1);
}

static int	check_num_philos(char *str)
{
	if (ft_atol(str) > 200)
		return (1);
	return (0);
}

int	args_parser(char **argv)
{
	int		i;
	long	comparer;

	i = 0;
	while (argv[++i])
		check_string(argv[i]);
	i = 0;
	if (check_num_philos(argv[1]))
		return (param_error(1));
	while (argv[++i])
	{
		comparer = ft_atol(argv[i]);
		if (comparer > INT_MAX || comparer <= 0)
			return (param_error(i));
	}
	return (0);
}
