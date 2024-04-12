/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 18:18:43 by matorgue          #+#    #+#             */
/*   Updated: 2024/04/12 22:23:08 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init(t_data *data, char **av, int ac)
{
	if (ac != 5 && ac != 6)
		return (ft_putstr_fd("probleme avec les arguments\n", 2), -1);
	pthread_mutex_init(&data->mutex_for_died, NULL);
	pthread_mutex_init(&data->mutex_for_eat, NULL);
	pthread_mutex_init(&data->mutex_for_look_died, NULL);
	data->start = get_time();
	data->number_of_philosophers = ft_atoi(av[1]);
	data->num = 0;
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = (uint64_t)ft_atoi(av[2]);
	data->time_to_eat = (uint64_t)ft_atoi(av[3]);
	data->time_to_sleep = (uint64_t)ft_atoi(av[4]);
	if (data->number_of_philosophers < 1 || data->time_to_die < 0
		|| data->time_to_die > 1000000 || data->time_to_eat < 0
		|| data->time_to_eat > 1000000 || data->time_to_sleep < 0
		|| data->time_to_sleep > 1000000)
		return (write(2, "probleme avec les argv\n", 23), -1);
	data->number_of_times_each_philosopher_must_eat = 300000000;
	data->philo_deads = false;
	if (ac == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	return (0);
}

void	ft_init_philo(t_data *data)
{
	int	i;

	i = 1;
	data->philo[0].fork_right = &data->forks[data->number_of_philosophers - 1];
	data->philo[0].fork_left = &data->forks[0];
	data->philo[0].philo_number = 0;
	data->philo[0].data = data;
	data->philo[0].for_sleep = false;
	data->philo[0].eat = false;
	data->philo[0].died = false;
	data->philo[0].must_eat = data->number_of_times_each_philosopher_must_eat;
	while (i < data->number_of_philosophers)
	{
		data->philo[i].philo_number = i;
		data->philo[i].for_sleep = false;
		data->philo[i].fork_right = &data->forks[i - 1];
		data->philo[i].fork_left = &data->forks[i];
		data->philo[i].data = data;
		data->philo[i].last_eat = get_time() * i - data->start * i;
		data->philo[i].must_eat = data->philo[0].must_eat;
		data->philo[i].eat = false;
		data->philo[i].died = false;
		i++;
	}
}

void	main_end(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(data->tt[i], NULL))
			exit(0);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->mutex_for_died);
	pthread_mutex_destroy(&data->mutex_for_eat);
	pthread_mutex_destroy(&data->mutex_for_look_died);
	free(data->forks);
	free(data->tt);
	free(data->philo);
	free(data);
}

void	main_end_first(t_data *data)
{
	int	i;

	i = 0;
	ft_init_philo(data);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->mutex_for_eat);
		data->philo[i].last_eat = get_time() - data->start;
		pthread_mutex_unlock(&data->mutex_for_eat);
		if (pthread_create(&data->tt[i], NULL, routine, &data->philo[i]))
			exit(0);
		i++;
	}
	main_end(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "probleme avec les argv\n", 23), 0);
	data = malloc(1 * sizeof(t_data));
	if (data == NULL)
		return (ft_putstr_fd("probleme de malloc\n", 2), 0);
	if (ft_init(data, av, ac) == -1)
		return (free(data), -1);
	data->tt = malloc(data->number_of_philosophers * sizeof(pthread_t));
	if (!data->tt)
		return (ft_putstr_fd("probleme de malloc\n", 2), 0);
	data->forks = malloc(data->number_of_philosophers
			* sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_putstr_fd("probleme de malloc\n", 2), 0);
	data->philo = malloc(data->number_of_philosophers * sizeof(t_philo));
	if (!data->philo)
		return (ft_putstr_fd("probleme de malloc\n", 2), 0);
	main_end_first(data);
	return (0);
}
