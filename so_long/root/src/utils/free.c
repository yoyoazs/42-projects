/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:06:39 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/26 18:59:06 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_game(t_game *data)
{
	int	y;

	y = -1;
	if (data->map && data->map->structure)
	{
		while (data->map->structure[++y])
			free(data->map->structure[y]);
		free(data->map->structure);
	}
	gc_exit(data->memory_table);
}

void	free_map(t_game *data, char **map)
{
	int	i;

	i = -1;
	while (map[++i])
		gc_free(data->memory_table, map[i]);
	gc_free(data->memory_table, map);
}
