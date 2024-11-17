/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:31:47 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 15:04:42 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook_space(t_game *data)
{
	t_player	*player;
	const int	direction = data->player->direction;

	player = data->player;
	if (data->state == 1)
	{
		data->state = 2;
		data->start_ms = get_milliseconds();
		return ;
	}
	if (data->state == 5 || data->state == 6)
		free_game(data);
	if (player->attack == 0 && !(on_ladder(data) && direction == CLIMBING))
		player->attack = 6;
}

void	hook_top(t_game *data)
{
	t_player	*player;

	player = data->player;
	if (on_ladder(data))
	{
		player->movement = CLIMBING;
		player->direction = CLIMBING;
	}
	else if (!check_fall(data, player->x, player->y, 2)
		&& player->is_jumping == 0
		&& check_move(data, init_pos(player->x, player->y), UP, false))
	{
		player->is_jumping = 1;
		player->last_sprite = 0;
	}
}

int	key_hook_down(int keycode, t_game *data)
{
	if (keycode == KEY_ESC)
		free_game(data);
	else if (keycode == KEY_SPACE)
		hook_space(data);
	else if (keycode == KEY_A || keycode == KEY_Q)
	{
		data->player->movement = LEFT;
		if (!(on_ladder(data) && data->player->direction == CLIMBING))
			data->player->direction = LEFT;
	}
	else if (keycode == KEY_D)
	{
		data->player->movement = RIGHT;
		if (!(on_ladder(data) && data->player->direction == CLIMBING))
			data->player->direction = RIGHT;
	}
	else if ((keycode == KEY_W || keycode == KEY_Z))
		hook_top(data);
	else if (keycode == KEY_S && on_ladder(data))
	{
		data->player->movement = DOWN;
		data->player->direction = CLIMBING;
	}
	return (0);
}

int	key_hook_up(int keycode, t_game *data)
{
	if (keycode == KEY_A || keycode == KEY_Q)
		data->player->movement = IDLE;
	else if (keycode == KEY_D)
		data->player->movement = IDLE;
	else if ((keycode == KEY_W || keycode == KEY_Z || keycode == KEY_S)
		&& on_ladder(data))
		data->player->movement = IDLE;
	return (0);
}
