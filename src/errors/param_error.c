/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-cas <juan-cas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:31:01 by juan-cas          #+#    #+#             */
/*   Updated: 2024/12/19 20:53:37 by juan-cas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philosophers.h"

int	param_error(int i)
{
	printf(RED "Please check the following argument and correct it:\n" RST);
	if (i == 1)
		printf(G "Philo # error: can only be from 1 to 200\n" RST);
	if (i == 2)
		printf(G "The time to die must be more than 0 and be numbers\n" RST);
	if (i == 3)
		printf(G "The time to eat must be more than 0 and be numbers\n" RST);
	if (i == 4)
		printf(G "The time to sleep must be more than 0 and be numbers\n" RST);
	if (i == 5)
		printf(G "How many times to eat must be more than 0\n" RST);
	return (1);
}
