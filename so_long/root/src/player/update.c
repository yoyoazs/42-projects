/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:59:25 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 08:33:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_jump(t_game *data, t_player *player)
{
	if (player->velocity_y >= 0
		|| !check_move(data, init_pos(player->x, player->y), UP, false))
	{
		player->velocity_y = 0;
		player->is_jumping = 0;
		return (0);
	}
	return (1);
}

static void	handle_jump(t_game *data)
{
	t_player	*player;
	const long	ms = get_milliseconds();

	player = data->player;
	if (player->is_jumping > 0)
	{
		if (ms - player->last_jump <= 240
			&& !check_fall(data, player->x, player->y, 5))
		{
			player->is_jumping = 0;
			return ;
		}
		player->last_jump = ms;
		player->velocity_y += GRAVITY;
		player->is_jumping = 2;
		if (!check_fall(data, player->x, player->y, 5))
		{
			player->velocity_y = JUMP_VELOCITY;
			player->number_movement++;
		}
		if (check_jump(data, player))
			player->y += player->velocity_y;
	}
}

void	update_player(t_game *data)
{
	data->player->last_x = data->player->x;
	data->player->last_y = data->player->y;
	handle_jump(data);
	handle_movement(data);
	if (on_ladder(data)
		&& check_fall(data, data->player->x, data->player->y, 5))
	{
		data->player->direction = CLIMBING;
		data->player->is_jumping = 0;
	}
}

void	init_player(t_game *data)
{
	data->player->movement = IDLE;
	data->player->health = 5;
	data->player->is_jumping = 0;
	data->player->direction = RIGHT;
	data->player->last_sprite = 0;
	data->player->last_damage = 0;
	data->player->number_movement = 0;
	data->player->collectables = 0;
	data->player->number_damage = 0;
	data->player->number_jump = 0;
	data->player->number_kill = 0;
	data->player->velocity_y = 0;
	data->player->last_jump = 0;
	data->player->last_mov = 0;
	data->ms = 0;
	data->player->attack = 0;
}
