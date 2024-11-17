/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:58:10 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 11:46:56 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_rect(t_form form, t_image *img)
{
	int	x_pos;
	int	y_pos;

	x_pos = -1;
	while (++x_pos < form.width)
	{
		y_pos = -1;
		while (++y_pos < form.height)
			pixel_put(img, init_sprite(x_pos + form.x,
					y_pos + form.y, 16026102));
	}
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	error_file(t_game *data, char *asset, int dir)
{
	if (dir == 1)
		ft_printf("%s%s: Is a directory%s.\n", ERROR_FORMAT, asset, RESET_COLOR);
	else
		ft_printf("%s%s: No such file%s.\n", ERROR_FORMAT, asset, RESET_COLOR);
	free_game(data);
	exit(1);
}

int	check_file(t_game *data, char *asset)
{
	int		fd;

	fd = open(asset, O_RDONLY);
	if (open(asset, O_RDONLY | O_DIRECTORY) > -1)
	{
		close(fd);
		error_file(data, asset, true);
	}
	if (fd <= 0)
		error_file(data, asset, false);
	close(fd);
	return (0);
}

unsigned long	get_milliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec << 10) + (tv.tv_usec >> 10));
}
