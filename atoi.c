/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 18:12:58 by matorgue          #+#    #+#             */
/*   Updated: 2024/01/25 18:35:17 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	long	nbr;
	long	neg;
	long	i;

	nbr = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] < 14 && str[i] > 8))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		nbr = ((nbr * 10) + (str[i] - 48));
		i++;
	}
	nbr = nbr * neg;
	return (nbr);
}
