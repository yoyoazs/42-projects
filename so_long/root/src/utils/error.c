/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:37:33 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 08:21:24 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error_map(t_game *data, char *str)
{
	ft_printf("%s%s%s\n", ERROR_FORMAT, str, RESET_COLOR);
	free_game(data);
	exit(1);
}
