/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:35:22 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/19 10:48:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_routine(t_philo *philo, int *nb_off_philo)
{
	int	start;

	pthread_mutex_lock(philo->data_mutex);
	start = philo->data->data_start;
	pthread_mutex_unlock(philo->data_mutex);
	while (!start)
	{
		pthread_mutex_lock(philo->data_mutex);
		start = philo->data->data_start;
		pthread_mutex_unlock(philo->data_mutex);
		usleep(10);
	}
	pthread_mutex_lock(philo->data_mutex);
	*nb_off_philo = philo->data->nb_philo;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->data_mutex);
	if (philo->id % 2)
		ft_usleep(philo->time_eat * 0.10);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		nb_off_philo;

	philo = (t_philo *)arg;
	init_philo_routine(philo, &nb_off_philo);
	if (nb_off_philo == 1)
	{
		philo_print(philo, FORK);
		return (ft_usleep(philo->data->time_to_die), NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->one_philo_dead)
			return (pthread_mutex_unlock(&philo->data->data_mutex), NULL);
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (!philo_eat(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static int	start_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_create(&data->philos[i].thread, NULL,
			&philo_routine, &data->philos[i]);
	pthread_mutex_lock(&data->data_mutex);
	data->start_time = get_time();
	data->data_start = 1;
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
	{
		printf("Error: invalid arguments.\n");
		return (1);
	}
	init_data(&data, argc, argv);
	if (init_philo(&data))
	{
		printf("Error: failed to initialize philosophers.\n");
		return (1);
	}
	start_philo(&data);
	monitor(&data);
	return (0);
}
