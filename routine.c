/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 19:00:00 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/12 23:08:42 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_fork(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_lock(&philo->data->mutex_for_eat);
		philo->eat = false;
		pthread_mutex_unlock(&philo->data->mutex_for_eat);
		philo->for_sleep = true;
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_lock(&philo->data->mutex_for_eat);
		philo->eat = false;
		pthread_mutex_unlock(&philo->data->mutex_for_eat);
		philo->for_sleep = true;
	}
}

void	ft_sleep(t_philo *philo, int *i)
{
	philo->for_sleep = false;
	timestamp(philo->data, 2, philo->philo_number);
	ft_usleep(philo->data->time_to_sleep);
	timestamp(philo->data, 3, philo->philo_number);
	ft_usleep((philo->data->time_to_eat - philo->data->time_to_sleep + 1));
	(*i)++;
}

void	routine_eat(t_philo *philo, int *i)
{
	pthread_mutex_lock(&philo->data->mutex_for_eat);
	if (philo->data->number_of_philosophers >= 2 && verif(philo) == 1
		&& first_eat(philo) == 1)
	{
		lock_fork(philo);
		pthread_mutex_unlock(&philo->data->mutex_for_eat);
		ft_usleep(philo->data->time_to_eat);
		unlock_fork(philo);
		ft_sleep(philo, i);
	}
	else
		pthread_mutex_unlock(&philo->data->mutex_for_eat);
	// if (philo->for_sleep == true && philo->last_eat
	// 	+ philo->data->time_to_sleep > philo->data->time_to_die)
	// 	ft_sleep(philo, i);
}

void	routine_deads(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_for_look_died);
	timestamp(philo->data, 4, philo->philo_number);
}

void	*routine(void *argv)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)argv;
	if (philo->philo_number % 2 == 0)
		ft_usleep(20);
	while (i < philo->must_eat)
	{
		routine_eat(philo, &i);
		philo->eats = get_time() - philo->data->start;
		pthread_mutex_lock(&philo->data->mutex_for_died);
		if (philo->died == true)
			return (pthread_mutex_unlock(&philo->data->mutex_for_died), NULL);
		pthread_mutex_unlock(&philo->data->mutex_for_died);
		pthread_mutex_lock(&philo->data->mutex_for_look_died);
		if (philo->eats - philo->last_eat > philo->data->time_to_die)
		{
			routine_deads(philo);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->mutex_for_look_died);
		usleep(1);
	}
	philo->last_eat = get_time();
	return (NULL);
}
