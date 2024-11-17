/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_item.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 16:26:50 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/18 00:39:31 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_collectable(t_game *data)
{
	int	x;
	int	y;

	x = (data->player->x + 50) / 100;
	y = (data->player->y + 50) / 100;
	if (data->map->structure[y][x] == 'C')
	{
		data->map->structure[y][x] = '0';
		data->map->collectables--;
		data->player->collectables++;
		return (1);
	}
	return (0);
}

int	on_ladder(t_game *data)
{
	int			pos_start;
	const int	pos_end = 78;
	int			number_pixel_ladder;
	int			x;
	int			y;

	number_pixel_ladder = 0;
	pos_start = 25;
	while (pos_start < pos_end)
	{
		x = (data->player->x + pos_start) / 100;
		y = (data->player->y + 50) / 100;
		if (data->map->structure[y][x] == 'L'
			&& data->map->structure[(data->player->y + 95) / 100][x] == 'L')
			number_pixel_ladder++;
		pos_start++;
	}
	if (number_pixel_ladder > 24)
		return (1);
	return (0);
}

int	can_exit(t_game *data)
{
	int	x;
	int	y;

	x = (data->player->x + 50) / 100;
	y = (data->player->y + 50) / 100;
	if (data->map->collectables <= 0 && data->map->structure[y][x] == 'E')
		return (1);
	return (0);
}
