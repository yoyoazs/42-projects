/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:00:28 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/19 11:23:17 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_write(int id, long long time, const char *colors,
const char *messages)
{
	char			buffer[50];
	char			time_str[20];
	char			id_str[10];
	int				len;
	const int		buffer_size = sizeof(buffer);

	len = 0;
	ft_itoa(time, time_str);
	ft_itoa(id, id_str);
	ft_bzero(buffer, sizeof(buffer));
	len += ft_strlcpy(buffer + len, colors, buffer_size - len);
	len += ft_strlcpy(buffer + len, time_str, buffer_size - len);
	len += ft_strlcpy(buffer + len, " ", buffer_size - len);
	len += ft_strlcpy(buffer + len, id_str, buffer_size - len);
	len += ft_strlcpy(buffer + len, " ", buffer_size - len);
	len += ft_strlcpy(buffer + len, messages, buffer_size - len);
	len += ft_strlcpy(buffer + len, RESET_COLOR, buffer_size - len);
	len += ft_strlcpy(buffer + len, "\n", buffer_size - len);
	write(1, buffer, len);
}

void	philo_print(t_philo *philo, int type)
{
	long long	time;
	int			dead;
	const char	*messages[] = {EAT_MESSAGE, SLEEP_MESSAGE,
		THINK_MESSAGE, FORK_MESSAGE};
	const char	*colors[] = {EAT_COLOR, SLEEP_COLOR, THINK_COLOR, FORK_COLOR};

	pthread_mutex_lock(philo->print_mutex);
	pthread_mutex_lock(philo->data_mutex);
	dead = philo->data->one_philo_dead;
	time = get_time() - philo->data->start_time;
	pthread_mutex_unlock(philo->data_mutex);
	if (dead)
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	philo_write(philo->id, time, colors[type], messages[type]);
	pthread_mutex_unlock(philo->print_mutex);
}

int	philo_eat(t_philo *philo)
{
	long long	current_time;

	take_fork(philo);
	pthread_mutex_lock(philo->data_mutex);
	current_time = get_time();
	if (current_time - philo->last_meal >= philo->data->time_to_die)
	{
		philo->data->one_philo_dead = 1;
		drop_fork(philo);
		pthread_mutex_unlock(philo->data_mutex);
		return (0);
	}
	philo->last_meal = current_time;
	pthread_mutex_unlock(philo->data_mutex);
	philo_print(philo, EAT);
	pthread_mutex_lock(philo->data_mutex);
	philo->nb_meals++;
	pthread_mutex_unlock(philo->data_mutex);
	ft_usleep(philo->time_eat);
	drop_fork(philo);
	return (1);
}

void	philo_think(t_philo *philo)
{
	long long	time_to_think;

	pthread_mutex_lock(philo->data_mutex);
	if (philo->data->nb_philo % 2 == 0)
	{
		pthread_mutex_unlock(philo->data_mutex);
		philo_print(philo, THINK);
		return ;
	}
	time_to_think = (philo->last_meal + philo->data->time_to_die) - get_time();
	pthread_mutex_unlock(philo->data_mutex);
	philo_print(philo, THINK);
	if (time_to_think <= 0)
		return ;
	ft_usleep(time_to_think * 0.5);
}

void	philo_sleep(t_philo *philo)
{
	philo_print(philo, SLEEP);
	ft_usleep(philo->time_sleep);
}
