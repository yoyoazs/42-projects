/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:01:54 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:31:28 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_move_abscissa(t_game *data, t_pos pos, int movement)
{
	const int	x = pos.x;
	const int	y = pos.y;

	if (movement == LEFT)
		if (data->map->structure[(y + 10) / 100][(x + 5) / 100] == '1' \
			|| data->map->structure[(y + 95) / 100][(x + 5) / 100] == '1')
			return (0);
	if (movement == RIGHT)
		if (data->map->structure[(y + 10) / 100][(x + 88) / 100] == '1' \
			|| data->map->structure[(y + 95) / 100][(x + 88) / 100] == '1')
			return (0);
	return (1);
}

static inline void	update_number_mov(t_game *data, t_pos pos)
{	
	const unsigned long	ms = get_milliseconds();
	const char			**map = (const char **)data->map->structure;
	t_player			*player;
	const int			x = pos.x;
	const int			y = pos.y;

	player = data->player;
	if (ms - player->last_mov > 60)
	{
		if (player->movement == CLIMBING
			&& !(map[(y + 30) / 100][(x + 20) / 100] == 'L' \
			|| map[(y + 30) / 100][(x + 75) / 100] == 'L'))
			return ;
		player->number_movement++;
		player->last_mov = ms;
	}
}

static int	check_move_ordonnee(t_game *data, t_pos pos, int movement,
	int print)
{
	const int	x = pos.x;
	const int	y = pos.y;
	const char	**map = (const char **)data->map->structure;
	const int	vy = data->player->velocity_y;

	if (movement == DOWN)
		if (map[(y + 115) / 100][(x + 25) / 100] == '1' \
			|| map[(y + 115) / 100][(x + 70) / 100] == '1')
			return (0);
	if (movement == UP)
	{
		if (data->player->is_jumping)
		{
			if (map[(y - vy - 2) / 100][(x + 20) / 100] == '1' \
				|| map[(y - vy - 2) / 100][(x + 75) / 100] == '1')
				return (0);
		}
		else if (map[(y - 10) / 100][(x + 20) / 100] == '1' \
			|| map[(y - 10) / 100][(x + 75) / 100] == '1')
			return (0);
	}
	if (print)
		update_number_mov(data, pos);
	return (1);
}

int	check_move(t_game *data, t_pos pos, int movement, int print)
{
	const int	x = pos.x;
	const int	y = pos.y;

	if (data->player->health <= 0 && print)
		return (0);
	if (check_move_abscissa(data, pos, movement) == 0)
		return (0);
	if (check_move_ordonnee(data, pos, movement, print) == 0)
		return (0);
	if (movement == CLIMBING && !(on_ladder(data)
			&& check_move(data, init_pos(x, y), UP, false)
			&& (data->map->structure[(y + 30) / 100][(x + 40) / 100] == 'L')))
		return (0);
	return (1);
}
