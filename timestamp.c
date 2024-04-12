/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:22:27 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/12 23:10:35 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	tinestamp_deads(t_data *data, uint64_t now, int nb)
{
	int	i;

	ft_usleep(1);
	pthread_mutex_lock(&data->mutex_for_died);
	if (data->philo_deads)
	{
		pthread_mutex_unlock(&data->mutex_for_died);
		return ;
	}
	printf("%ld %d died\n", (now - data->start), nb);
	data->philo_deads = true;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].died = true;
		i++;
	}
	pthread_mutex_unlock(&data->mutex_for_died);
}

void	timestamp(t_data *data, int i, int nb)
{
	uint64_t	now;

	now = get_time();
	//ft_usleep(1);
	pthread_mutex_lock(&data->mutex_for_died);
	if (data->philo[nb].died == true)
	{
		pthread_mutex_unlock(&data->mutex_for_died);
		return ;
	}
	if (i == 0)
		printf("%ld %d has taken a fork\n", (now - data->start), nb);
	if (i == 1)
		printf("%ld %d is eating\n", (now - data->start), nb);
	if (i == 2)
		printf("%ld %d is sleeping\n", (now - data->start), nb);
	if (i == 3)
		printf("%ld %d is thinking\n", (now - data->start), nb);
	pthread_mutex_unlock(&data->mutex_for_died);
	if (i == 4)
		tinestamp_deads(data, now, nb);
}
