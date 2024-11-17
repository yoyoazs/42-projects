/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 21:43:32 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/19 10:14:29 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi_safe(argv[1]);
	data->time_to_die = ft_atoi_safe(argv[2]);
	data->time_to_eat = ft_atoi_safe(argv[3]);
	data->time_to_sleep = ft_atoi_safe(argv[4]);
	data->start_time = 0;
	if (argc == 6)
		data->nb_meals = ft_atoi_safe(argv[5]);
	else
		data->nb_meals = -1;
	data->philos = NULL;
	data->forks = NULL;
	data->data_start = 0;
	data->one_philo_dead = 0;
}

static void	destroy_fork_init(t_data *data, int i)
{
	while (i > 0)
		pthread_mutex_destroy(&data->forks[--i]);
}

static int	init_threads(t_data *data)
{
	int				i;
	const long long	time = get_time();

	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			break ;
		data->philos[i].id = i + 1;
		data->philos[i].nb_meals = 0;
		data->philos[i].last_meal = 0;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].data_mutex = &data->data_mutex;
		data->philos[i].time_eat = data->time_to_eat;
		data->philos[i].time_sleep = data->time_to_sleep;
		data->philos[i].data = data;
		data->philos[i].time_start = time;
		data->philos[i].thread = 0;
	}
	if (i != data->nb_philo)
		return (destroy_fork_init(data, i), 1);
	return (0);
}

static int	init_mutexs(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (destroy_fork_mutex(data), 1);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (destroy_fork_mutex(data), 1);
	}
	return (0);
}

int	init_philo(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		free(data->philos);
		return (1);
	}
	if (init_threads(data))
		return (1);
	return (init_mutexs(data));
}
