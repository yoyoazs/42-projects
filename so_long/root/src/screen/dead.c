/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 22:37:13 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 15:07:53 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_dead_screen(t_game *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->screen_y / 100)
	{
		x = -1;
		while (++x < data->screen_x / 100 + 1)
			pus_img(data, init_sprite(x * 100, y * 100, FLOOR),
				data->images->wall_sprite);
	}
	draw_text(data, strdup("You died"),
		init_sprite(data->screen_x / 2 - 250, data->screen_y / 2 - 200, 140),
		data->image);
	draw_text(data, strdup("Press space to close"),
		init_sprite(data->screen_x / 2 - 500, data->screen_y / 2 + 50, 120),
		data->image);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img_ptr, 0, 0);
}
