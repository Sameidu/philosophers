/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/06/07 20:46:25 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_nap(long long useconds, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	long long		init;
	long long		present;

	gettimeofday(&start, NULL);
	init = start.tv_sec * 1000000 + start.tv_usec;
	while (1)
	{
		gettimeofday(&current, NULL);
		present = current.tv_sec * 1000000 + current.tv_usec;
		if ((present - init >= useconds)
			|| (philo && (ft_im_dead(philo) || check_philo_dead(philo))))
			break ;
		usleep(500);
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_error(void *node, char *str)
{
	if (node)
		free(node);
	printf("%s\n", str);
	return (1);
}

int	ft_isnum(int c)
{
	return (c >= '0' && c <= '9');
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
