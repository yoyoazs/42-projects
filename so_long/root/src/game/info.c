/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:49:00 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 20:18:24 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_pos_info(t_game *data, int *x, int *y, bool rect)
{
	int	width;
	int	height;

	get_pos_item(data, &width, &height);
	*y = 10;
	*x = data->screen_x - 210;
	if (data->map->len * 100 <= data->screen_x)
		*x = data->map->len * 100 - 210;
	if (!rect)
	{
		*x += width;
		*y += height;
	}
}

void	draw_info(t_game *data)
{
	int	x;
	int	y;
	int	i;

	get_pos_info(data, &x, &y, true);
	i = -1;
	draw_rect(init_form(x, y, 200, 80), data->image_print);
	get_pos_info(data, &x, &y, false);
	while (data->player->health > 0 && ++i < data->player->health)
		push_img_game(data, init_sprite(x + 5 + (40 * i), y, 1),
			data->images->heart_sprite);
	if (i < 5 && i > 0)
		i--;
	while (++i < 5)
		push_img_game(data, init_sprite(x + 5 + (40 * i), y, 3),
			data->images->heart_sprite);
	get_pos_info(data, &x, &y, true);
	draw_text_left(data, ft_itoa(data->player->number_movement),
		init_sprite(x + 150, y + 28, 50), data->image_print);
}
