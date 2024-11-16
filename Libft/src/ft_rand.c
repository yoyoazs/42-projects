/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:37:49 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/11/14 10:54:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdint.h>

uint32_t	ft_rand(int min, int max)
{
	static uintptr_t	seed = 0;
	int					local_var;

	if (min >= max)
		return (0);
	if (seed == 0)
		seed = (uintptr_t) & local_var;
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return ((seed % (max - min + 1)) + min);
}
