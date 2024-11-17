/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:45:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:09:20 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_pos_item(t_game *data, int *x, int *y)
{
	*y = data->player->y - (data->screen_y - 100) / 2;
	*x = data->player->x - (data->screen_x - 100) / 2;
	if (data->map->len * 100 <= data->screen_x)
		*x = 0;
	else if (*x < 0)
		*x = 0;
	else if (*x > (data->map->len * 100 - data->screen_x))
		*x = data->map->len * 100 - data->screen_x;
	if (data->map->width * 100 <= data->screen_y)
		*y = 0;
	else if (*y < 0)
		*y = 0;
	else if (*y > (data->map->width * 100 - data->screen_y))
		*y = data->map->width * 100 - data->screen_y;
}

static void	update_door(t_game *data)
{
	static int	door = 1;

	if (data->map->collectables <= 0 && door != 7)
		door++;
	push_img_game(data, init_sprite(data->map->exit_x * 100,
			data->map->exit_y * 100, door / 2 + 1), data->images->door_sprite);
}

static void	update_collectable(t_game *data)
{
	t_collectable	*collectable;

	on_collectable(data);
	data->sprite_collectable++;
	if (data->sprite_collectable >= 28)
		data->sprite_collectable = 0;
	collectable = data->collectables;
	while (collectable)
	{
		if (data->map->structure[collectable->y][collectable->x] == 'C')
		{
			push_img_game(data, init_sprite(collectable->x * 100 + 25,
					collectable->y * 100 + 33, (data->sprite_collectable / 7)
					+ 1), data->images->collectable_sprite);
		}
		collectable = collectable->next;
	}
}

void	push_img_game(t_game *data, t_sprite sp, t_image *img)
{
	int	px;
	int	x;
	int	y;
	int	sp_x;
	int	sp_y;

	get_pos_item(data, &x, &y);
	sp_x = -1;
	while (++sp_x < img->width)
	{
		sp_y = -1;
		while (++sp_y < img->height)
		{
			if (sp.x + sp_x >= x && sp.y + sp_y >= y
				&& sp.x + sp_x < x + data->image_print->width
				&& sp.y + sp_y < y + data->image_print->height)
			{
				px = get_pixel_value(data, sp, img, init_pos(sp_x, sp_y));
				if (px > 0)
					pixel_put(data->image_print,
						init_sprite(sp.x + sp_x - x, sp.y + sp_y - y, px));
			}
		}
	}
}

void	update_map(t_game *data)
{
	t_sprite	player;

	if (data->image_print)
		draw_image_on_window(data, data->image_print);
	if (can_exit(data))
		data->state++;
	update_player(data);
	if (data->player->health <= -9)
		data->state = 5;
	get_visible_map(data);
	update_enemy(data);
	update_door(data);
	update_collectable(data);
	draw_info(data);
	player = init_sprite(data->player->x, data->player->y,
			get_next_sprite(data, data->player->movement));
	player.is_player = 1;
	push_img_game(data, player, data->images->player_sprite);
}
