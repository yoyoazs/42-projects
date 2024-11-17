/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 08:06:09 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/19 10:49:21 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

long long	get_time(void)
{
	struct timeval	current_time;
	long long		ms;

	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (ms);
}

int	ft_atoi_safe(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] == '0')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	if (ft_atoi_safe(argv[1]) < 0 || ft_atoi_safe(argv[2]) < 0
		|| ft_atoi_safe(argv[3]) < 0 || ft_atoi_safe(argv[4]) < 0)
		return (1);
	if (ft_atoi_safe(argv[2]) < 1 || ft_atoi_safe(argv[3]) < 1
		|| ft_atoi_safe(argv[4]) < 1)
		return (1);
	if (argc == 6 && ft_atoi_safe(argv[5]) < 1)
		return (1);
	return (0);
}

void	ft_usleep(long long time_ms)
{
	long long	start_time;
	long long	elapsed_time;
	long long	remaining_time;

	if (time_ms <= 0)
		return ;
	start_time = get_time();
	elapsed_time = 0;
	while (elapsed_time < time_ms)
	{
		remaining_time = time_ms - elapsed_time;
		usleep(remaining_time * 0.50);
		elapsed_time = get_time() - start_time;
	}
}
