/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:37:49 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/31 14:04:29 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uint32_t	ft_rand(int min, int max)
{
	static uintptr_t	seed = 0;

	if (min >= max)
		return (0);
	if (seed == 0)
		seed = (uintptr_t) & seed;
	seed = (seed * 1103515245 + 12345) & 0x7fffffff;
	return ((seed % (max - min)) + min);
}
