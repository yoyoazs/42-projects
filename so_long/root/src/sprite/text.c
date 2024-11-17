/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:03:00 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/24 21:28:50 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_pos_char(char c, int *x, int *y)
{
	const char	list[41] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$:?!";

	*x = -1;
	*y = 0;
	while (list[++(*x)])
	{
		if (list[*x] == c)
			break ;
	}
	while (*x > 7)
	{
		*x -= 8;
		(*y)++;
	}
}

void	draw_char(t_game *data, t_sprite sprite, char c, t_image *img)
{
	int	x;
	int	y;
	int	pos_x;
	int	pos_y;
	int	original_pixel_index;

	get_pos_char(ft_toupper(c), &pos_x, &pos_y);
	y = -1;
	while (++y < sprite.sprite)
	{
		x = -1;
		while (++x < sprite.sprite)
		{
			original_pixel_index = ((y * 240 / sprite.sprite) + (pos_y * 240))
				* data->images->alphanum_sprite->size_line
				+ ((x * 240 / sprite.sprite) + (pos_x * 240))
				* data->images->alphanum_sprite->bpp / 8;
			if (data->images->alphanum_sprite->data[original_pixel_index] != 0)
				pixel_put(img, init_sprite(sprite.x + x,
						sprite.y + y, 789517));
		}
	}
}

void	draw_text(t_game *data, char *str, t_sprite sprite, t_image *img)
{
	int			i;
	const int	x_base = sprite.x;

	i = -1;
	if (str == NULL)
		return ;
	while (str[++i])
	{
		if (str[i] == '\n')
		{
			sprite.x = x_base;
			sprite.y += sprite.sprite / 3 + 5;
		}
		else if (str[i] == ' ')
			sprite.x += sprite.sprite / 3;
		else
		{
			draw_char(data, sprite, str[i], img);
			sprite.x += sprite.sprite / 3 + 5;
		}
	}
	free(str);
}

void	draw_text_left(t_game *data, char *str, t_sprite sprite, t_image *img)
{
	int			i;
	const int	x_base = sprite.x;

	i = ft_strlen(str) - 1;
	if (str == NULL)
		return ;
	while (i >= 0 && str[i])
	{
		if (str[i] == '\n')
		{
			sprite.x = x_base;
			sprite.y += sprite.sprite / 3 + 5;
		}
		else if (str[i] == ' ')
			sprite.x -= sprite.sprite / 3;
		else
		{
			draw_char(data, sprite, str[i], img);
			sprite.x -= sprite.sprite / 3 + 5;
		}
		i--;
	}
	free(str);
}
