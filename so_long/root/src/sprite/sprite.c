/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:38:32 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/25 15:07:27 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	pixel_put(t_image *img, t_sprite sprite)
{
	const int	y = sprite.y;
	const int	x = sprite.x;
	const int	offset = (y * img->size_line) + (x * (img->bpp / 8));

	*((unsigned int *)(img->data + offset)) = sprite.sprite;
}

int	get_pixel_player(t_game *data, int px)
{
	long long	ms;

	ms = get_milliseconds() - data->player->last_damage;
	if (ms > 2500)
		return (px);
	if ((ms >= 0 && ms <= 250) || (ms >= 750 && ms <= 1000)
		|| (ms >= 1500 && ms <= 1750) || (ms >= 2250 && ms <= 2500))
	{
		if (px != 268607)
			px = 16777215;
	}
	return (px);
}

int	get_pixel_value(t_game *data, t_sprite sprite, t_image *img, t_pos pos)
{
	const int	x = pos.x;
	const int	y = pos.y;
	int			sprite_offset;
	int			px;

	if (sprite.sprite >= 0)
		sprite_offset = x + ((sprite.sprite - 1) * img->width);
	else
		sprite_offset = -sprite.sprite * img->width - x;
	if (!(x >= 0 && x < img->width && y >= 0 && y < img->height))
		return (-1);
	px = *((int *)(img->data + y * img->size_line
				+ (sprite_offset * img->bpp / 8)));
	if (sprite.is_player && px > 0)
		px = get_pixel_player(data, px);
	return (px);
}

void	pus_img(t_game *data, t_sprite sprite, t_image *img)
{
	int			x_2;
	int			y_2;
	int			px;

	x_2 = -1;
	while (++x_2 < img->width)
	{
		y_2 = -1;
		while (++y_2 < img->height)
		{
			px = get_pixel_value(data, sprite, img, init_pos(x_2, y_2));
			if (px > 0)
				pixel_put(data->image,
					init_sprite(sprite.x + x_2, sprite.y + y_2, px));
		}
	}
}
