/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 23:43:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 18:40:42 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extension(char *file, char *extension)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (file[i])
		i++;
	while (extension[j])
		j++;
	if (i < j)
		return (0);
	while (j >= 0)
	{
		if (file[i] != extension[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

char	**copy_map(t_game *data)
{
	char	**new_map;
	int		i;

	i = -1;
	new_map = gc_malloc(data->memory_table, sizeof(char *)
			* (data->map->width + 1));
	while (++i < data->map->width)
		new_map[i] = gc_strdup(data->memory_table, data->map->structure[i]);
	new_map[i] = NULL;
	return (new_map);
}
