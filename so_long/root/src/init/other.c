/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 02:53:28 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:26:48 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static inline void	init_mlx_image(t_game *data, t_image *image,
int width, int height)
{
	t_block_info	*param;
	t_memory_table	*memory_table;

	memory_table = data->memory_table;
	image->img_ptr = mlx_new_image(data->mlx, width, height);
	image->width = width;
	image->height = height;
	image->data = mlx_get_data_addr(image->img_ptr,
			&image->bpp, &image->size_line, &image->endian);
	param = gc_malloc(memory_table, sizeof(t_block_info));
	param->ptr = data->mlx;
	param->ptr2 = image->img_ptr;
	gc_add_memory_block(memory_table, image->img_ptr, destroy_mlx_img, param);
	gc_free(memory_table, param);
}

static inline void	init_mlx_images(t_game *data)
{
	int	width;
	int	height;

	if (data->screen_x > data->map->len * 100)
		width = data->screen_x;
	else
		width = data->map->len * 100;
	if (data->screen_y > data->map->width * 100)
		height = data->screen_y;
	else
		height = data->map->width * 100;
	data->image = gc_malloc(data->memory_table, sizeof(t_image));
	init_mlx_image(data, data->image, width, height);
	if (data->screen_x < data->map->len * 100)
		width = data->screen_x;
	else
		width = data->map->len * 100;
	if (data->screen_y < data->map->width * 100)
		height = data->screen_y;
	else
		height = data->map->width * 100;
	data->image_print = gc_malloc(data->memory_table, sizeof(t_image));
	init_mlx_image(data, data->image_print, width, height);
}

int	init_mlx(t_game *data)
{
	t_block_info	*info;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (error_map(data, "Mlx not found."));
	info = gc_malloc(data->memory_table, sizeof(t_block_info));
	info->ptr = data->mlx;
	gc_add_memory_block(data->memory_table, data->mlx, destroy_mlx, info);
	gc_free(data->memory_table, info);
	mlx_get_screen_size(data->mlx, &data->screen_x, &data->screen_y);
	data->win = mlx_new_window(data->mlx, data->screen_x, data->screen_y,
			"So_long by ybeaucou");
	if (!data->win)
		return (error_map(data, "Window not found."));
	info = gc_malloc(data->memory_table, sizeof(t_block_info));
	info->ptr = data->mlx;
	info->ptr2 = data->win;
	gc_add_memory_block(data->memory_table, data->win, destroy_mlx_win, info);
	gc_free(data->memory_table, info);
	init_mlx_images(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img_ptr, 0, 0);
	return (0);
}

void	init_all_images(t_game *data)
{
	check_file(data, "./assets/sprites/wall_sprite.xpm");
	check_file(data, "./assets/sprites/player_sprite.xpm");
	check_file(data, "./assets/sprites/enemy_sprite.xpm");
	check_file(data, "./assets/sprites/collectable_sprite.xpm");
	check_file(data, "./assets/sprites/alphanum_sprite.xpm");
	check_file(data, "./assets/sprites/key_sprite.xpm");
	check_file(data, "./assets/sprites/heart_sprite.xpm");
	check_file(data, "./assets/sprites/door_sprite.xpm");
	data->images = gc_malloc(data->memory_table, sizeof(t_images));
	data->images->wall_sprite = init_image(data, "wall", 100, 100);
	data->images->player_sprite = init_image(data, "player", 100, 100);
	data->images->enemy_sprite = init_image(data, "enemy", 100, 100);
	data->images->collectable_sprite = init_image(data, "collectable", 50, 50);
	data->images->alphanum_sprite = init_image(data, "alphanum", 240, 240);
	data->images->key_sprite = init_image(data, "key", 60, 60);
	data->images->heart_sprite = init_image(data, "heart", 35, 32);
	data->images->door_sprite = init_image(data, "door", 100, 100);
}

int	init_map(t_game *data, int argc, char **argv)
{
	if (argc < 2)
		return (error_map(data, "Usage: ./so_long <map> [username]"));
	else if (argc > 3)
		return (error_map(data, "Usage: ./so_long <map> [username]"));
	else if (!get_map(data, argv[1]))
		return (error_map(data, "Map not found"));
	if (argc == 3)
		data->player->username = argv[2];
	else
		data->player->username = "player1";
	return (0);
}
