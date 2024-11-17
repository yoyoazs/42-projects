/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:47:58 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/26 08:02:44 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*thread_func(void *arg)
{
	t_thread_args	*args;
	t_game			*data;
	int				y;
	int				x;

	args = (t_thread_args *)arg;
	y = args->start_y;
	data = args->data;
	while (++y < args->end_y + 1)
	{
		x = -1;
		while (++x < data->image_print->width)
			pixel_put(data->image_print, init_sprite(x, y,
					get_pixel_value(data, init_sprite(x + args->start_x,
							y + args->y, 0), data->image,
						init_pos(x + args->start_x, y + args->y))));
	}
	pthread_exit(NULL);
}

void	get_visible_map(t_game *data)
{
	pthread_t		threads[NUMBER_THREAD];
	t_thread_args	thread_args[NUMBER_THREAD];
	int				x;
	int				y;
	int				i;

	get_pos_item(data, &x, &y);
	i = -1;
	while (++i < NUMBER_THREAD)
	{
		thread_args[i].data = data;
		thread_args[i].start_x = x;
		thread_args[i].start_y = i * data->image_print->height / NUMBER_THREAD;
		thread_args[i].y = y;
		thread_args[i].end_y = ((i == NUMBER_THREAD - 1)
				* data->image_print->height) + (i != NUMBER_THREAD - 1)
			* (i + 1) * data->image_print->height / NUMBER_THREAD;
		pthread_create(&threads[i], NULL, thread_func, (void *)&thread_args[i]);
	}
	i = -1;
	while (++i < NUMBER_THREAD)
		pthread_join(threads[i], NULL);
}
