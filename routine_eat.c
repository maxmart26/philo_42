/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_eat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:54:17 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/12 22:10:29 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_first_eat_0(t_philo *philo, t_data *data)
{
	if (data->philo[1].last_eat < philo->last_eat
		&& data->philo[data->number_of_philosophers].last_eat < philo->last_eat)
		return (0);
	else
		return (1);
}

int	ft_first_eat_last(t_philo *philo, t_data *data)
{
	if (data->philo[0].last_eat < philo->last_eat
		&& data->philo[data->number_of_philosophers
		- 1].last_eat < philo->last_eat)
		return (0);
	else
		return (1);
}

int	ft_first_eat_nb(t_philo *philo, t_data *data)
{
	if (data->philo[philo->philo_number + 1].last_eat < philo->last_eat
		&& data->philo[data->number_of_philosophers
		- 1].last_eat < philo->last_eat)
		return (0);
	else
		return (1);
}
int	first_eat(t_philo *philo)
{
	uint64_t	now;
	int			i;
	t_data		*data;
	int			k;

	k = 0;
	data = philo->data;
	i = 0;
	now = get_time() - data->start;
	if (philo->philo_number == 0)
		return (ft_first_eat_0(philo, data));
	else if (philo->philo_number == data->number_of_philosophers)
		return (ft_first_eat_last(philo, data));
	else
		return (ft_first_eat_nb(philo, data));
}

int	verif(t_philo *philo)
{
	if (philo->philo_number == philo->data->number_of_philosophers - 1)
	{
		if (philo->data->philo[0].eat == false
			&& philo->data->philo[philo->philo_number - 1].eat == false)
			return (1);
	}
	else if (philo->philo_number == 0)
	{
		if (philo->data->philo[philo->data->number_of_philosophers
				- 1].eat == false && philo->data->philo[1].eat == false)
			return (1);
	}
	else
	{
		if (philo->data->philo[philo->philo_number + 1].eat == false
			&& philo->data->philo[philo->philo_number - 1].eat == false)
			return (1);
	}
	return (0);
}

void	ft_usleep(uint64_t sleep)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < sleep)
	{
		usleep(sleep / 10);
	}
}

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	timestamp(philo->data, 0, philo->philo_number);
	pthread_mutex_lock(philo->fork_right);
	timestamp(philo->data, 0, philo->philo_number);
	philo->eat = true;
	timestamp(philo->data, 1, philo->philo_number);
	philo->last_eat = get_time() - philo->data->start;
}
