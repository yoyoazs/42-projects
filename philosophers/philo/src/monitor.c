/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:23:35 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/18 13:58:46 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	exit_thread(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philos[i].thread, NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(data->philos[i].right_fork);
	free(data->philos);
	free(data->forks);
}

static void	philo_print_dead(t_philo *philo)
{
	long long	time;

	pthread_mutex_lock(philo->print_mutex);
	time = get_time();
	printf("%s%llu %d %s%s\n", DEAD_COLOR, time - philo->time_start, philo->id,
		DEAD_MESSAGE, RESET_COLOR);
	pthread_mutex_unlock(philo->print_mutex);
}

static int	set_end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	data->one_philo_dead = 1;
	pthread_mutex_unlock(&data->data_mutex);
	return (1);
}

static int	check_status_philo(t_data *data)
{
	int			i;
	long long	ms;
	int			finished;

	finished = 1;
	i = -1;
	while (++i < data->nb_philo)
	{
		ms = get_time();
		pthread_mutex_lock(&data->data_mutex);
		if (ms - data->philos[i].last_meal > data->time_to_die
			&& data->philos[i].last_meal != 0)
		{
			data->one_philo_dead = 1;
			pthread_mutex_unlock(&data->data_mutex);
			return (philo_print_dead(&data->philos[i]), 1);
		}
		else if (data->nb_meals == -1 || (data->nb_meals > 0
				&& data->philos[i].nb_meals < data->nb_meals))
			finished = 0;
		pthread_mutex_unlock(&data->data_mutex);
	}
	if (finished)
		return (set_end_simulation(data));
	return (0);
}

void	monitor(t_data *data)
{
	int	time_to_die;

	pthread_mutex_lock(&data->data_mutex);
	time_to_die = data->time_to_die;
	pthread_mutex_unlock(&data->data_mutex);
	while (1)
	{
		if (check_status_philo(data))
			break ;
		usleep(100);
	}
	exit_thread(data);
}
