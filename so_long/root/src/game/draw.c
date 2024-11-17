/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:55:54 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 12:25:10 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_sprite_map(t_game *data, int x, int y)
{
	if (data->map->structure[y][x] == '1')
		return (get_wall_sprite(data, x, y));
	if (data->map->structure[y][x] == 'E')
	{
		pus_img(data, init_sprite(x * 100, y * 100, FLOOR),
			data->images->wall_sprite);
		return (FLOOR);
	}
	if (data->map->structure[y][x] == 'L')
	{
		pus_img(data, init_sprite(x * 100, y * 100, FLOOR),
			data->images->wall_sprite);
		if (data->map->structure[y + 1][x] != 'L')
			return (49);
		return (50);
	}
	return (47);
}

void	draw_image_on_window(t_game *data, t_image *img)
{
	int	y;
	int	x;

	y = (data->screen_y - (data->map->width + 1) * 100) / 2;
	x = (data->screen_x - data->map->len * 100) / 2;
	if (data->map->len * 100 > data->screen_x)
		x = 0;
	if (data->map->width * 100 > data->screen_y)
		y = 0;
	if (y < 0)
		y = 0;
	if (x < 0)
		x = 0;
	mlx_put_image_to_window(data->mlx, data->win, img->img_ptr, x, y);
}

int	draw_map(t_game *data)
{
	int	x;
	int	y;

	y = -1;
	data->state++;
	mlx_do_sync(data->mlx);
	mlx_clear_window(data->mlx, data->win);
	init_player(data);
	while (data->map->structure[++y])
	{
		x = -1;
		while (data->map->structure[y][++x])
		{
			if (get_sprite_map(data, x, y) <= 100)
				pus_img(data, init_sprite(x * 100, y * 100,
						get_sprite_map(data, x, y)), data->images->wall_sprite);
			else
				pus_img(data, init_sprite(x * 100, y * 100,
						get_sprite_map(data, x, y) - 100),
					data->images->door_sprite);
		}
	}
	return (0);
}
