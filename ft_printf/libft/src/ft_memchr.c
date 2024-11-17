/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:22:16 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/12 03:26:45 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	char			*string;

	i = -1;
	string = (void *)s;
	while (++i < n)
		if (string[i] == (char)c)
			return (&string[i]);
	return (NULL);
}
