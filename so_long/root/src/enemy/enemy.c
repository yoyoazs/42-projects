/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:15:06 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/01 16:02:00 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_enemy(t_game *data)
{
	int		direction;
	t_enemy	*tp;
	char	**map;

	map = data->map->structure;
	tp = data->enemies;
	while (tp)
	{
		if (tp->alive)
		{
			direction = -1;
			if (tp->direction == RIGHT)
				direction = 1;
			tp->last_x = tp->x;
			tp->last_y = tp->y;
			if (map[(tp->y / 100) + 1][(tp->x + 80) / 100] != '1'
				&& map[(tp->y / 100) + 1][(tp->x + 8) / 100] != '1')
				tp->y += 10;
			else if (check_move(data, init_pos(tp->x, tp->y), tp->direction, 0))
				tp->x += 3 * direction;
			else
				tp->direction += direction;
		}
		tp = tp->next;
	}
}

static void	give_damage(t_game *data)
{
	t_enemy	*tmp;

	tmp = data->enemies;
	while (tmp)
	{
		if (tmp->alive && (tmp->x + 50) / 100 == (data->player->x + 50) / 100
			&& (tmp->y + 50) / 100 == (data->player->y + 50) / 100)
		{
			if (get_milliseconds() - data->player->last_damage > 2500)
			{
				data->player->health--;
				data->player->last_damage = get_milliseconds();
				tmp->attack = 14;
				tmp->sprite = 0;
				data->player->number_damage += 10;
				if (tmp->x < data->player->x)
					tmp->direction = RIGHT;
				else
					tmp->direction = LEFT;
			}
		}
		tmp = tmp->next;
	}
}

static void	take_damage(t_game *data)
{
	int		add;
	t_enemy	*tmp;

	tmp = data->enemies;
	if (data->player->attack == 6 || data->player->attack == 3)
	{
		if (data->player->direction == RIGHT)
			add = 78;
		if (data->player->direction == LEFT)
			add = 24;
		while (tmp)
		{
			if (tmp->alive
				&& (tmp->x + 50) / 100 == (data->player->x + add) / 100
				&& (tmp->y + 50) / 100 == (data->player->y + 50) / 100)
			{
				tmp->dying = 10;
				tmp->alive = false;
				data->player->number_kill++;
			}
			tmp = tmp->next;
		}
	}
}

void	update_enemy(t_game *data)
{
	move_enemy(data);
	take_damage(data);
	give_damage(data);
	draw_enemy(data);
}
