/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natrijau <natrijau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:16:33 by natrijau          #+#    #+#             */
/*   Updated: 2024/04/02 17:26:56 by natrijau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atoi(const char *nptr)
{
	long int	i;
	long int	nb;

	i = 0;
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

bool	its_integer(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);	
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (false);
		i++;
	}
	return (true);
}
bool	all_positiv_num(char **av)
{
	if (ft_atoi(av[1]) < 0
		|| ft_atoi(av[2]) < 0
			|| ft_atoi(av[3]) < 0
				|| ft_atoi(av[4]) < 0)
	return (false);
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (false);
	return (true);
}

long int current_time(void)
{
	struct timeval my_time;
  	long int current_time;
	gettimeofday(&my_time, NULL);
	current_time = (my_time.tv_sec * 1000) + (my_time.tv_usec / 1000);
	return(current_time);
}