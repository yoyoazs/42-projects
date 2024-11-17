/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:36:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 20:18:24 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_number_sprite(t_enemy *tmp)
{
	if (tmp->dying > 0)
		tmp->sprite = (tmp->sprite + 1) % 10;
	else if (tmp->attack > 0)
		tmp->sprite = (tmp->sprite + 1) % 14;
	else
		tmp->sprite = (tmp->sprite + 1) % 9;
}

static void	draw_enemy_sprite(t_game *data, t_enemy *tmp, int d)
{
	if (tmp->dying == 10)
		tmp->sprite = 0;
	if (tmp->dying-- > 0)
		push_img_game(data, init_sprite(tmp->x, tmp->y,
				(tmp->sprite / 2 + 10) * d), data->images->enemy_sprite);
	else if (tmp->attack-- > 0)
		push_img_game(data, init_sprite(tmp->x, tmp->y,
				(tmp->sprite + 15) * d), data->images->enemy_sprite);
	else
		push_img_game(data, init_sprite(tmp->x, tmp->y,
				((tmp->sprite / 3) + 1) * d), data->images->enemy_sprite);
}

void	draw_enemy(t_game *data)
{
	t_enemy	*tmp;
	int		d;

	tmp = data->enemies;
	while (tmp)
	{
		d = -1;
		if (tmp->alive || tmp->dying > 0)
		{
			if (tmp->direction == LEFT)
				d = 1;
			draw_enemy_sprite(data, tmp, d);
			update_number_sprite(tmp);
		}
		tmp = tmp->next;
	}
}
