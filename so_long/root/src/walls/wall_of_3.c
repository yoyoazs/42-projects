/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_of_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:03:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/22 14:48:17 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline int	get_wall_sprite_3_2(t_game *data, int x, int y)
{
	if (is_wall(data, x, y - 1) && is_wall(data, x, y + 1)
		&& is_wall(data, x - 1, y))
	{
		if (!is_wall(data, x - 1, y - 1) && !is_wall(data, x - 1, y + 1))
			return (38);
		if (!is_wall(data, x - 1, y + 1))
			return (36);
		if (!is_wall(data, x - 1, y - 1))
			return (27);
		return (9);
	}
	if (is_wall(data, x, y - 1) && is_wall(data, x, y + 1)
		&& is_wall(data, x + 1, y))
	{
		if (!is_wall(data, x + 1, y - 1) && !is_wall(data, x + 1, y + 1))
			return (20);
		if (!is_wall(data, x + 1, y - 1))
			return (18);
		if (!is_wall(data, x + 1, y + 1))
			return (14);
		return (2);
	}
	return (0);
}

int	get_wall_sprite_3(t_game *data, int x, int y)
{
	if (is_wall(data, x - 1, y) && is_wall(data, x + 1, y)
		&& is_wall(data, x, y - 1))
	{
		if (!is_wall(data, x - 1, y - 1) && !is_wall(data, x + 1, y - 1))
			return (26);
		if (!is_wall(data, x - 1, y - 1))
			return (41);
		if (!is_wall(data, x + 1, y - 1))
			return (31);
		return (44);
	}
	if (is_wall(data, x - 1, y) && is_wall(data, x + 1, y)
		&& is_wall(data, x, y + 1))
	{
		if (!is_wall(data, x - 1, y + 1) && !is_wall(data, x + 1, y + 1))
			return (22);
		if (!is_wall(data, x - 1, y + 1))
			return (32);
		if (!is_wall(data, x + 1, y + 1))
			return (21);
		return (15);
	}
	return (get_wall_sprite_3_2(data, x, y));
}
