/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:12:30 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/15 13:34:38 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			dstsize;
	size_t			srcsize;

	if (dst == NULL && src != NULL && size == 0)
		return (0);
	srcsize = ft_strlen(src);
	dstsize = ft_strlen(dst);
	if (size <= dstsize)
		return (size + srcsize);
	i = 0;
	while (dstsize + i < size - 1 && src[i])
	{
		dst[dstsize + i] = src[i];
		i++;
	}
	dst[dstsize + i] = '\0';
	if (dstsize < size)
		return (dstsize + srcsize);
	return (size + srcsize);
}
