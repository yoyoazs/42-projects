/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 17:09:20 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 14:12:32 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_charactere2(int *x, int *y, t_game *data)
{
	if (data->map->structure[*y][*x] == 'P')
	{
		data->player->x = (*x) * 100;
		data->player->y = (*y) * 100;
	}
	if (data->map->structure[*y][*x] == 'C')
		data->map->collectables++;
	if (data->map->structure[*y][*x] == 'B')
		data->map->number_enemy++;
	if (data->map->len != (int)ft_strlen(data->map->structure[*y]))
		error_map(data, "Map is not a rectangle.");
}

void	check_charactere(int *x, int *y, int *number_exit, t_game *data)
{
	while (data->map->structure[++(*y)])
	{
		*x = -1;
		while (data->map->structure[*y][++(*x)])
		{
			if (!ft_strchr("01PECBL", data->map->structure[*y][*x]))
				error_map(data, "Map contain an unauthorized character");
			if ((*y == 0 && data->map->structure[*y][*x] != '1') ||
				(!(data->map->structure[*y + 1])
				&& data->map->structure[*y][*x] != '1')
				|| (*x == 0 && data->map->structure[*y][*x] != '1')
				|| (!(data->map->structure[*y][*x + 1])
				&& data->map->structure[*y][*x] != '1'))
				error_map(data, "Map is not closed.");
			if (data->map->structure[*y][*x] == 'P' && data->player->x != 0)
				error_map(data, "Too many players.");
			if (data->map->structure[*y][*x] == 'E')
			{
				(*number_exit)++;
				data->map->exit_x = *x;
				data->map->exit_y = *y;
			}
			check_charactere2(x, y, data);
		}
	}
}

int	check_map(t_game *data)
{
	int	y;
	int	x;
	int	number_exit;

	y = -1;
	number_exit = 0;
	data->map->collectables = 0;
	data->sprite_collectable = 0;
	data->player = gc_malloc(data->memory_table, sizeof(t_player));
	data->map->number_enemy = 0;
	data->player->x = 0;
	data->map->len = ft_strlen(data->map->structure[0]);
	check_charactere(&x, &y, &number_exit, data);
	if (number_exit != 1)
		return (error_map(data, "No exit or too many exits."));
	if (data->player->x == 0)
		return (error_map(data, "No player."));
	if (data->map->collectables == 0)
		return (error_map(data, "No collectable."));
	data->map->width = y;
	return (check_valid_path(data));
}

char	*set_map(t_game *data, char *path)
{
	char	*str;
	char	*gnl;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		gc_free(data->memory_table, path);
		error_map(data, "Map not found.");
	}
	str = get_next_line(fd);
	gnl = gc_strdup(data->memory_table, "");
	while (str)
	{
		gnl = gc_strjoin(data->memory_table, gnl, str);
		free(str);
		str = get_next_line(fd);
		if (str && str[0] == '\n')
			str[0] = '9';
	}
	close(fd);
	free(str);
	return (gnl);
}

int	get_map(t_game *data, char *map)
{
	char	*path;
	char	*gnl;

	if (!check_extension(map, ".ber"))
		error_map(data, "Map is not .ber file.");
	path = gc_strjoin(data->memory_table, NULL, MAPS_DIR);
	path = gc_strjoin(data->memory_table, path, map);
	check_file(data, path);
	gnl = set_map(data, path);
	gc_free(data->memory_table, path);
	if (!gnl)
		error_map(data, "Map is empty.");
	data->map = gc_malloc(data->memory_table, sizeof(t_map));
	data->map->structure = NULL;
	data->map->structure = ft_split(gnl, '\n');
	gc_free(data->memory_table, gnl);
	if (!data->map->structure)
		error_map(data, "Map is empty.");
	return (check_map(data));
}
