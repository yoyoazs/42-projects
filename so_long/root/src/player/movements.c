/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:43:17 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:28:37 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_abscissa(t_game *data, t_player *player, int check)
{
	int		move;
	int		x;
	char	**map;

	move = 5;
	map = data->map->structure;
	while (move > 0)
	{
		x = (player->x + check + move) / 100;
		if (map[(player->y + 98) / 100][x] != '1'
			&& map[(player->y + 3) / 100][x] != '1')
		{
			if (player->movement == RIGHT)
				player->x += move;
			else
				player->x -= move;
		}
		else
			move--;
	}
}

static void	check_ordonnee(t_game *data, t_player *player, int check)
{
	int		move;
	int		y;
	char	**map;

	move = 5;
	map = data->map->structure;
	while (move > 0)
	{
		y = (player->y + move + check) / 100;
		if (map[y][(player->x + 25) / 100] != '1'
			&& map[y][(player->x + 70) / 100] != '1')
			player->y += move;
		else
			move--;
	}
}

static void	handle_precis_movement(t_game *data)
{
	t_player	*player;
	int			check;

	player = data->player;
	if (player->movement == RIGHT)
		check = 90;
	else if (player->movement == LEFT)
		check = 10;
	if (player->movement == RIGHT || player->movement == LEFT)
		check_abscissa(data, player, check);
	else if (player->movement == DOWN && on_ladder(data))
		check_ordonnee(data, player, 99);
}

void	handle_movement(t_game *data)
{
	t_player	*player;

	player = data->player;
	if (player->is_jumping == 0 && player->movement != CLIMBING)
		gravity(data);
	if (player->movement == RIGHT)
		if (check_move(data, init_pos(player->x, player->y), RIGHT, true))
			player->x += MOVE_X;
	if (player->movement == LEFT)
		if (check_move(data, init_pos(player->x, player->y), LEFT, true))
			player->x -= MOVE_X;
	if (player->movement == CLIMBING)
		if (check_move(data, init_pos(player->x, player->y), CLIMBING, true))
			player->y -= MOVE_Y;
	if (on_ladder(data) && player->movement == DOWN)
		if (check_move(data, init_pos(player->x, player->y), DOWN, true))
			player->y += MOVE_Y;
	if (player->x == player->last_x && player->y == player->last_y)
		handle_precis_movement(data);
}
