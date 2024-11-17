/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_of_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:01:19 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/21 19:02:52 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_wall_sprite_2_2(t_game *data, int x, int y)
{
	if (is_wall(data, x + 1, y) && is_wall(data, x, y - 1))
	{
		if (!is_wall(data, x + 1, y - 1))
			return (43);
		return (13);
	}
	if (is_wall(data, x + 1, y) && is_wall(data, x - 1, y))
		return (19);
	if (is_wall(data, x, y + 1) && is_wall(data, x, y - 1))
		return (24);
	return (0);
}

int	get_wall_sprite_2(t_game *data, int x, int y)
{
	if (is_wall(data, x + 1, y) && is_wall(data, x, y + 1))
	{
		if (!is_wall(data, x + 1, y + 1))
			return (37);
		return (46);
	}
	if (is_wall(data, x - 1, y) && is_wall(data, x, y + 1))
	{
		if (!is_wall(data, x - 1, y + 1))
			return (42);
		return (40);
	}
	if (is_wall(data, x - 1, y) && is_wall(data, x, y - 1))
	{
		if (!is_wall(data, x - 1, y - 1))
			return (33);
		return (6);
	}
	return (get_wall_sprite_2_2(data, x, y));
}
