/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:37:16 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:43:33 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_sprite_number(t_game *data)
{
	int			i;
	const int	limits[] = {30, 20, 20, 20, 18};
	int			*counters[5];

	counters[0] = &data->start_game->sprite_attack;
	counters[1] = &data->start_game->sprite_climb;
	counters[2] = &data->start_game->sprite_idle;
	counters[3] = &data->start_game->sprite_jump;
	counters[4] = &data->start_game->sprite_run;
	i = -1;
	while (++i < 5)
	{
		(*counters[i])++;
		if (*counters[i] == limits[i])
			*counters[i] = 0;
	}
}

static void	update_sprite(t_game *data, t_sprite sprite, int action)
{
	const int	x = sprite.x;
	int			y;
	t_image		*img_wall;
	t_image		*img_player;

	y = sprite.y;
	img_wall = data->images->wall_sprite;
	img_player = data->images->player_sprite;
	pus_img(data, init_sprite(x, y, FLOOR), img_wall);
	if (action == 3)
		pus_img(data, init_sprite(x, y - 100, FLOOR), img_wall);
	if (action == 4)
		pus_img(data, init_sprite(x, y, 49), img_wall);
	pus_img(data, init_sprite(x, y, sprite.sprite), img_player);
}

void	updade_sreen_start(t_game *dt)
{
	const int		x = (dt->screen_x - 70) - ((dt->screen_x - 70) % 100);
	t_start_game	*g;

	g = dt->start_game;
	update_sprite_number(dt);
	update_sprite(dt, init_sprite(x - 2100, 200, g->sprite_idle / 5 + 20), 1);
	update_sprite(dt, init_sprite(x - 2100, 500, g->sprite_run / 3 + 32), 2);
	update_sprite(dt, init_sprite(x - 300, 200, g->sprite_jump / 3 + 24), 3);
	update_sprite(dt, init_sprite(x - 300, 500, g->sprite_climb / 5 + 8), 4);
	update_sprite(dt, init_sprite(x / 2, 700, g->sprite_attack / 5 + 2), 5);
	mlx_do_sync(dt->mlx);
	mlx_put_image_to_window(dt->mlx, dt->win, dt->image->img_ptr, 0, 0);
}

static void	draw_touch(t_game *data)
{
	t_image		*img;
	const int	x = (data->screen_x - 70) - ((data->screen_x - 70) % 100);
	t_image		*img_wall;

	img = data->images->key_sprite;
	img_wall = data->images->wall_sprite;
	pus_img(data, init_sprite(x - 2100 + 45, 200 + 100, 23), img_wall);
	pus_img(data, init_sprite(x - 2100 - 55, 200 + 100, 12), img_wall);
	pus_img(data, init_sprite(x - 2100 + 45, 500 + 100, 23), img_wall);
	pus_img(data, init_sprite(x - 2100 - 55, 500 + 100, 12), img_wall);
	pus_img(data, init_sprite(x - 300 + 45, 200 + 100, 23), img_wall);
	pus_img(data, init_sprite(x - 300 - 55, 200 + 100, 12), img_wall);
	pus_img(data, init_sprite(x - 300 + 45, 500 + 100, 23), img_wall);
	pus_img(data, init_sprite(x - 300 - 55, 500 + 100, 12), img_wall);
	pus_img(data, init_sprite(x / 2 + 45, 700 + 100, 23), img_wall);
	pus_img(data, init_sprite(x / 2 - 55, 700 + 100, 12), img_wall);
	pus_img(data, init_sprite(x - 2130, 620, 1), img);
	pus_img(data, init_sprite(x - 2035, 620, 2), img);
	pus_img(data, init_sprite(x - 280, 320, 4), img);
	pus_img(data, init_sprite(x - 330, 620, 4), img);
	pus_img(data, init_sprite(x - 230, 620, 3), img);
	pus_img(data, init_sprite(x / 2 - 15, 825, 5), img);
	pus_img(data, init_sprite(x / 2 + 45, 825, 6), img);
}

void	draw_screen_start(t_game *data)
{
	int	x;
	int	y;

	data->state = 1;
	data->start_game = gc_malloc(data->memory_table, sizeof(t_start_game));
	data->start_game->sprite_attack = 0;
	data->start_game->sprite_climb = 0;
	data->start_game->sprite_idle = 0;
	data->start_game->sprite_jump = 0;
	data->start_game->sprite_run = 0;
	y = -1;
	while (++y < data->screen_y / 100)
	{
		x = -1;
		while (++x < data->screen_x / 100 + 1)
			pus_img(data, init_sprite(x * 100, y * 100, FLOOR),
				data->images->wall_sprite);
	}
	draw_text(data, ft_strdup("so long"),
		init_sprite(data->screen_x / 2 - 260, 450, 150), data->image);
	draw_text(data, ft_strdup("press space to continue"),
		init_sprite(600, 1000, 150), data->image);
	draw_touch(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img_ptr, 0, 0);
}
