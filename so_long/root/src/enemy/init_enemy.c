/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:57:17 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/24 21:28:45 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_lstadd_back_enemy(t_enemy **alst, t_enemy *new)
{
	t_enemy	*last;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	if (last && last->next)
		while (last->next)
			last = last->next;
	last->next = new;
}

static void	set_enemy(t_enemy *enemy, int x, int y, int direction)
{
	enemy->x = x * 100;
	enemy->y = y * 100;
	enemy->last_x = x;
	enemy->last_y = y;
	enemy->direction = direction;
	enemy->sprite = 0;
	enemy->attack = 0;
	enemy->alive = true;
	enemy->next = NULL;
	enemy->dying = 0;
}

void	init_enemy(t_game *data)
{
	t_enemy	*enemy;
	int		x;
	int		y;

	y = -1;
	while (data->map->structure[++y])
	{
		x = -1;
		while (data->map->structure[y][++x])
		{
			if (data->map->structure[y][x] == 'B')
			{
				enemy = gc_malloc(data->memory_table, sizeof(t_enemy));
				set_enemy(enemy, x, y, RIGHT);
				ft_lstadd_back_enemy(&data->enemies, enemy);
			}
		}
	}
}
