/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 22:41:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 18:25:26 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_fall(t_game *data, int x, int y, int fall)
{
	if (data->map->structure[(y + 99 + fall) / 100][(x + 20) / 100] == '1'
		|| data->map->structure[(y + 99 + fall) / 100][(x + 75) / 100] == '1')
		return (0);
	return (1);
}

void	gravity(t_game *data)
{
	t_player	*player;

	player = data->player;
	if (on_ladder(data))
		return ;
	player->velocity_y += GRAVITY;
	if (player->velocity_y > MAX_FALL_VELOCITY)
		player->velocity_y = MAX_FALL_VELOCITY;
	if (check_fall(data, player->x, player->y, player->velocity_y))
		player->y += player->velocity_y;
	else if (player->y % 100 != 0)
	{
		player->velocity_y = 0;
		player->y += (100 - player->y % 100);
	}
	else
		player->velocity_y = 0;
}
