/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:02:17 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:29:52 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_form	init_form(int x, int y, int width, int height)
{
	t_form	new_form;

	new_form.x = x;
	new_form.y = y;
	new_form.width = width;
	new_form.height = height;
	return (new_form);
}

t_sprite	init_sprite(int x, int y, int sprite)
{
	t_sprite	new_sprite;

	new_sprite.x = x;
	new_sprite.y = y;
	new_sprite.sprite = sprite;
	new_sprite.is_player = 0;
	return (new_sprite);
}

t_pos	init_pos(int x, int y)
{
	t_pos	new_pos;

	new_pos.x = x;
	new_pos.y = y;
	return (new_pos);
}

t_image	*init_image(t_game *data, char *file_path, int height, int width)
{
	t_block_info	*info;
	t_image			*sprite;
	char			*str;
	t_memory_table	*memory_table;

	memory_table = data->memory_table;
	str = gc_strdup(memory_table, "./assets/sprites/");
	str = gc_strjoin(memory_table, str, file_path);
	str = gc_strjoin(memory_table, str, "_sprite.xpm");
	sprite = gc_malloc(memory_table, sizeof(t_image));
	sprite->img_ptr = mlx_xpm_file_to_image(data->mlx, str,
			&sprite->width, &sprite->height);
	sprite->data = mlx_get_data_addr(sprite->img_ptr, &sprite->bpp,
			&sprite->size_line, &sprite->endian);
	sprite->height = height;
	sprite->width = width;
	info = gc_malloc(memory_table, sizeof(t_block_info));
	info->ptr = data->mlx;
	info->ptr2 = sprite->img_ptr;
	gc_add_memory_block(memory_table, sprite->img_ptr, destroy_mlx_img, info);
	gc_free(memory_table, info);
	gc_free(memory_table, str);
	return (sprite);
}
