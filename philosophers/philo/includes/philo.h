/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:36:10 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/19 10:51:08 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DEAD 4

// # define EAT_COLOR "\x1B[0;32m"
// # define SLEEP_COLOR "\x1B[0;33m"
// # define THINK_COLOR "\x1B[0;34m"
// # define DEAD_COLOR "\x1B[0;31m"
// # define FORK_COLOR "\x1B[0;35m"
// # define RESET_COLOR "\x1B[0m"

# define EAT_COLOR ""
# define SLEEP_COLOR ""
# define THINK_COLOR ""
# define DEAD_COLOR ""
# define FORK_COLOR ""
# define RESET_COLOR ""

# define EAT_MESSAGE "is eating"
# define SLEEP_MESSAGE "is sleeping"
# define THINK_MESSAGE "is thinking"
# define DEAD_MESSAGE "died"
# define FORK_MESSAGE "has taken a fork"

typedef struct s_philo
{
	int				id;
	int				nb_meals;
	long long		last_meal;
	long long		time_eat;
	long long		time_sleep;
	long long		time_start;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*data_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_meals;
	int				one_philo_dead;
	int				data_start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	data_mutex;
}	t_data;

//PHILO FUNCTION
int			philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		philo_print(t_philo *philo, int type);

//UTILS
int			ft_atoi_safe(const char *str);
long long	get_time(void);
void		ft_usleep(long long time);
int			check_args(int argc, char **argv);
void		destroy_fork_mutex(t_data *data);
char		*ft_itoa(long int n, char *str);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
void		ft_bzero(void *s, size_t n);

//INIT
void		init_data(t_data *data, int argc, char **argv);
int			init_philo(t_data *data);

//FORK
void		take_fork(t_philo *philo);
void		drop_fork(t_philo *philo);

void		monitor(t_data *data);

#endif