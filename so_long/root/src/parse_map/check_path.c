/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:36:40 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 14:20:58 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_path3(char **map, t_pos pos, t_pos pos2)
{
	const int	x = pos.x;
	const int	y = pos.y;

	if (x < (int)ft_strlen(map[y]) - 2 && map[y + 1][x + 1] != '1'
		&& map[y][x + 1] != '1' && map[y][x + 2] != '1' && map[y - 1][x] != '1'
		&& map[y - 1][x + 1] != '1' && map[y - 1][x + 2] != '1'
		&& check_path(map, init_pos(x + 2, y), pos2))
		return (1);
	if (x > 0 && map[y + 1][x - 1] != '1' && map[y][x - 1] != '1'
		&& map[y][x - 2] != '1' && map[y - 1][x] != '1'
		&& map[y - 1][x - 1] != '1' && map[y - 1][x - 2] != '1'
		&& check_path(map, init_pos(x - 2, y), pos2))
		return (1);
	return (0);
}

int	check_path2(char **map, t_pos pos, t_pos pos2)
{
	const int	x = pos.x;
	const int	y = pos.y;

	if ((map[y - 1][x + 1] != '1' && map[y - 1][x] != 'L')
		&& (map[y - 1][x] != '1' && map[y - 1][x + 1] != 'L')
		&& check_path(map, init_pos(x + 1, y - 1), pos2))
		return (1);
	if (y > 0 && x > 0 && map[y - 1][x - 1] != '1'
		&& map[y - 1][x] != '1'
		&& check_path(map, init_pos(x - 1, y - 1), pos2))
		return (1);
	if (x < (int)ft_strlen(map[y]) - 1 && map[y][x + 1] != '1'
		&& check_path(map, init_pos(x + 1, y), pos2))
		return (1);
	if (x > 0 && map[y][x - 1] != '1'
		&& check_path(map, init_pos(x - 1, y), pos2))
		return (1);
	return (check_path3(map, pos, pos2));
}

int	check_path(char **map, t_pos pos, t_pos pos2)
{
	const int	x2 = pos2.x;
	const int	y2 = pos2.y;
	const int	x = pos.x;
	int			y;

	y = pos.y;
	if ((y == y2 || (y - 1 == y2 && map[y + 1][x] == '1')) && x == x2)
		return (1);
	if (y < 0 || x < 0 || map[y][x] == '1')
		return (0);
	while (map[y + 1][x] != '1' && map[y][x] != 'L')
	{
		y++;
		if (y == y2 && x == x2)
			return (1);
	}
	if (map[y][x] == 'L' && map[y - 1][x] == 'L'
		&& check_path(map, init_pos(x, y - 1), pos2))
		return (1);
	if (map[y][x] == 'V')
		return (0);
	map[y][x] = 'V';
	if (check_path2(map, init_pos(x, y), pos2))
		return (1);
	return (0);
}

int	check_valid_path_collectable(t_game *data, t_pos pos,
t_collectable *collectable)
{
	char	**map;
	int		error;

	error = 0;
	map = copy_map(data);
	if (!check_path(map, pos, init_pos(collectable->x,
				collectable->y)))
		error = 1;
	pos.y = collectable->y;
	pos.x = collectable->x;
	free_map(data, map);
	return (error);
}

int	check_valid_path(t_game *data)
{
	char			**map;
	t_pos			pos;
	t_collectable	*collectable;
	int				error;

	error = 0;
	pos.x = data->player->x / 100;
	pos.y = data->player->y / 100;
	get_collectable(data);
	collectable = data->collectables;
	while (collectable != NULL && !error)
	{
		error = check_valid_path_collectable(data, pos, collectable);
		collectable = collectable->next;
	}
	map = copy_map(data);
	if (!check_path(map, pos, init_pos(data->map->exit_x, data->map->exit_y)))
		error = 1;
	free_map(data, map);
	if (error)
		return (error_map(data, "Invalid path to collectable or exit"));
	return (1);
}
