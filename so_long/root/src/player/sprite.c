/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:00:22 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 08:02:52 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_spitre_number(t_game *data, int max)
{
	data->player->last_sprite++;
	if (data->player->last_sprite >= max)
		data->player->last_sprite = 0;
}

static int	sprite_death_attack(t_game *data, int d)
{
	if (data->player->health <= 0)
	{
		data->player->movement = IDLE;
		if (data->player->health == 0)
		{
			data->player->health = -1;
			data->player->last_sprite = 1;
		}
		if (data->player->last_sprite == 15)
			data->player->health = -10;
		return ((12 + data->player->last_sprite++ / 2) * d);
	}
	if (data->player->movement != IDLE && data->player->movement != CLIMBING)
		return ((38 + data->player->attack--) * d);
	return ((1 + data->player->attack--) * d);
}

static void	get_out_ladder(t_game *data)
{
	const char	**map = (const char **)data->map->structure;
	t_player	*player;

	player = data->player;
	if (player->movement == LEFT || player->movement == RIGHT)
		player->direction = player->movement;
	if (player->movement == DOWN
		&& (map[player->y / 100][(player->x + 25) / 100] != 'L'
		&& map[player->y / 100][(player->x + 75) / 100] != 'L'))
		player->movement = IDLE;
}

static int	sprite_ladder(t_game *data, int d)
{
	update_spitre_number(data, 16);
	if (data->player->movement == IDLE)
		return (8);
	return ((data->player->last_sprite / 4 + 8) * d);
}

int	get_next_sprite(t_game *data, int movement)
{
	int	d;

	d = 1;
	if (data->player->direction == LEFT)
		d = -1;
	if (!on_ladder(data) && data->player->direction == CLIMBING)
		get_out_ladder(data);
	if (data->player->health <= 0 || data->player->attack > 0)
		return (sprite_death_attack(data, d));
	if (on_ladder(data))
		return (sprite_ladder(data, d));
	update_spitre_number(data, 24);
	if (data->player->is_jumping > 0)
		return ((data->player->last_sprite / 3 + 24) * d);
	if (movement == IDLE)
		return ((data->player->last_sprite / 6 + 20) * d);
	data->player->last_sprite--;
	update_spitre_number(data, 18);
	return ((data->player->last_sprite / 3 + 32) * d);
}
