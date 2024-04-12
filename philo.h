/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matorgue <warthog2603@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:19:39 by matorgue          #+#    #+#             */
/*   Updated: 2024/02/13 09:27:26 by matorgue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	uint64_t		eats;
	uint64_t		last_eat;
	int				philo_number;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	struct s_data	*data;
	long			must_eat;
	bool			eat;
	bool			died;
	bool			for_sleep;
}					t_philo;

typedef struct s_data
{
	bool			philo_deads;
	int				number_of_philosophers;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	uint64_t		start;
	pthread_t		*tt;
	int				num;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_for_eat;
	pthread_mutex_t	mutex_for_died;
	pthread_mutex_t	mutex_for_look_died;
	t_philo			*philo;

}					t_data;

void				timestamp(t_data *data, int i, int nb);
uint64_t			get_time(void);
long				ft_atoi(char *str);
void				ft_putstr_fd(char const *s, int fd);
void				*routine(void *argv);
void				ft_usleep(uint64_t sleep);

void				lock_fork(t_philo *philo);
void				ft_usleep(uint64_t sleep);
int					verif(t_philo *philo);
int					first_eat(t_philo *philo);
#endif
