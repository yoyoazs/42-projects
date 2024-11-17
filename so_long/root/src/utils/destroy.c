/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:57:50 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:29:40 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_mlx(t_block_info *ptr)
{
	mlx_destroy_display(ptr->ptr);
	free(ptr->ptr);
}

void	destroy_mlx_win(t_block_info *ptr)
{
	mlx_destroy_window(ptr->ptr, ptr->ptr2);
}

void	destroy_mlx_img(t_block_info *params)
{
	mlx_destroy_image(params->ptr, params->ptr2);
}
