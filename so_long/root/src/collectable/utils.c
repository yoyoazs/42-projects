/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:56:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/16 19:57:35 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	delete_collectable(t_game *data, int x, int y)
{
	t_collectable	*current;
	t_collectable	*previous;

	current = data->collectables;
	previous = NULL;
	while (current)
	{
		if (current->x == x && current->y == y)
		{
			if (previous)
			{
				previous->next = current->next;
				free(current);
				return ;
			}
			else
			{
				data->collectables = current->next;
				free(current);
				return ;
			}
		}
		previous = current;
		current = current->next;
	}
}

t_collectable	*sort_collectable(t_game *data, t_collectable *head)
{
	t_collectable	*i;
	t_collectable	*j;
	t_collectable	*tmp;

	i = head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_abs(data->map->exit_y - i->y)
				+ ft_abs(data->map->exit_x - i->x)
				> ft_abs(data->map->exit_y - j->y)
				+ ft_abs(data->map->exit_x - j->x))
			{
				tmp = i;
				i = j;
				j = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
	return (head);
}

void	get_collectable(t_game *data)
{
	init_collectable(data);
	data->collectables = sort_collectable(data, data->collectables);
}
