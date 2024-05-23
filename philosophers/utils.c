/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smeixoei <smeixoei@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:58:31 by smeixoei          #+#    #+#             */
/*   Updated: 2024/05/23 22:12:54 by smeixoei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time(void)
{
	t_time	init;

	gettimeofday(&init, NULL);
	return (init.tv_sec * 1000 + init.tv_usec / 1000);
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

void	ft_msg(t_philo *thread, char *str)
{
	t_philo	*philo;
	long	time;

	philo = thread;
	time = ft_time() - philo->time;
	pthread_mutex_lock(philo->write);
	if (*(philo->ph_dead) == 1)
	{
		pthread_mutex_unlock(philo->write);
		return ;
	}
	if (!strncmp(str, "fork", 3))
		printf("\033[0;33m%ld %d has taken a fork\n", time, philo->id);
	if (!strncmp(str, "eat", 3))
		printf("\033[0;32m%ld %d is eating\n", time, philo->id);
	if (!strncmp(str, "sleep", 5))
		printf("\033[0;36m%ld %d is sleeping\n", time, philo->id);
	if (!strncmp(str, "think", 5))
		printf("\033[0;35m%ld %d is thinking\n", time, philo->id);
	if (!strncmp(str, "dead", 4))
		printf("\033[0;31mPhilosopher %d died\n", philo->id);
	pthread_mutex_unlock(philo->write);
}

int	ft_error(t_philo *node, char *str)
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
