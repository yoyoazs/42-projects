/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:49:00 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 14:13:06 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <X11/Xlib.h>

static int	game_loop(t_game *data)
{
	if (get_milliseconds() - data->ms > 25)
	{
		data->ms = get_milliseconds();
		if (data->state == 0)
			draw_screen_start(data);
		else if (data->state == 1)
			updade_sreen_start(data);
		else if (data->state == 2)
			draw_map(data);
		else if (data->state == 3)
			update_map(data);
		else if (data->state == 4)
			draw_screen_end(data);
		else if (data->state == 5)
			draw_dead_screen(data);
	}
	return (0);
}

int	exit_game(t_game *data)
{
	free_game(data);
	return (0);
}

static void	play_games(t_game *data)
{
	init_player(data);
	data->state = 0;
	init_enemy(data);
	mlx_hook(data->win, 2, 1L << 0, key_hook_down, data);
	mlx_hook(data->win, 3, 1L << 1, key_hook_up, data);
	mlx_hook(data->win, 17, 1L << 17, exit_game, data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_game	data;

	ft_bzero(&data, sizeof(t_game));
	data.memory_table = gc_init();
	init_map(&data, argc, argv);
	init_mlx(&data);
	init_all_images(&data);
	play_games(&data);
	return (0);
}
