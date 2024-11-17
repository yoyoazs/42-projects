/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_of_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:05:26 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/23 13:48:57 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_wall_sprite_4_2(t_game *data, int x, int y)
{
	if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x + 1, y - 1))
		return (5);
	if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x - 1, y + 1))
		return (1);
	if (!is_wall(data, x - 1, y + 1) && !is_wall(data, x - 1, y - 1))
		return (10);
	if (!is_wall(data, x - 1, y - 1) && !is_wall(data, x + 1, y - 1))
		return (17);
	if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x - 1, y - 1))
		return (16);
	if (!is_wall(data, x + 1, y - 1) && !is_wall(data, x - 1, y + 1))
		return (4);
	if (!is_wall(data, x + 1, y + 1))
		return (39);
	if (!is_wall(data, x - 1, y + 1))
		return (45);
	if (!is_wall(data, x - 1, y - 1))
		return (11);
	if (!is_wall(data, x + 1, y - 1))
		return (25);
	return (3);
}

int	get_wall_sprite_4(t_game *data, int x, int y)
{
	if (is_wall(data, x + 1, y) && is_wall(data, x - 1, y)
		&& is_wall(data, x, y + 1) && is_wall(data, x, y - 1))
	{
		if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x + 1, y - 1)
			&& !is_wall(data, x - 1, y + 1) && !is_wall(data, x - 1, y - 1))
			return (8);
		if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x - 1, y + 1)
			&& !is_wall(data, x - 1, y - 1))
			return (35);
		if (!is_wall(data, x + 1, y - 1) && !is_wall(data, x - 1, y - 1)
			&& !is_wall(data, x + 1, y + 1))
			return (48);
		if (!is_wall(data, x + 1, y + 1) && !is_wall(data, x + 1, y - 1)
			&& !is_wall(data, x - 1, y + 1))
			return (29);
		if (!is_wall(data, x - 1, y + 1) && !is_wall(data, x - 1, y - 1)
			&& !is_wall(data, x + 1, y - 1))
			return (28);
		return (get_wall_sprite_4_2(data, x, y));
	}
	return (0);
}
