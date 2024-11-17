/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:50:39 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/24 21:28:46 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_lstadd_back_collectable(t_collectable **alst, t_collectable *new)
{
	t_collectable	*last;

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

static void	set_collectabl(t_collectable *collectable, int x, int y)
{
	collectable->x = x;
	collectable->y = y;
	collectable->next = NULL;
}

void	init_collectable(t_game *data)
{
	t_collectable	*item;
	int				x;
	int				y;

	y = -1;
	while (data->map->structure[++y])
	{
		x = -1;
		while (data->map->structure[y][++x])
		{
			if (data->map->structure[y][x] == 'C')
			{
				item = gc_malloc(data->memory_table, sizeof(t_collectable));
				set_collectabl(item, x, y);
				ft_lstadd_back_collectable(&data->collectables, item);
			}
		}
	}
}
