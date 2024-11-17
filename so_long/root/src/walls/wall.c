/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:08:58 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/21 21:39:23 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_wall(t_game *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->len || y >= data->map->width)
		return (1);
	if (data->map->structure[y][x] == '1')
		return (1);
	return (0);
}

static int	get_number_of_wall(t_game *data, int x, int y)
{
	int		nb;

	nb = 0;
	if (is_wall(data, x + 1, y))
		nb++;
	if (is_wall(data, x, y + 1))
		nb++;
	if (is_wall(data, x - 1, y))
		nb++;
	if (is_wall(data, x, y - 1))
		nb++;
	return (nb);
}

static int	get_wall_sprite_1(t_game *data, int x, int y)
{
	if (is_wall(data, x + 1, y))
		return (12);
	if (is_wall(data, x, y + 1))
		return (30);
	if (is_wall(data, x - 1, y))
		return (23);
	if (is_wall(data, x, y - 1))
		return (34);
	return (0);
}

int	get_wall_sprite(t_game *data, int x, int y)
{
	int			sprite;
	const int	nb_wall = get_number_of_wall(data, x, y);

	if (nb_wall == 1)
		sprite = get_wall_sprite_1(data, x, y);
	else if (nb_wall == 2)
		sprite = get_wall_sprite_2(data, x, y);
	else if (nb_wall == 3)
		sprite = get_wall_sprite_3(data, x, y);
	else
		sprite = get_wall_sprite_4(data, x, y);
	if (sprite)
		return (sprite);
	return (7);
}
