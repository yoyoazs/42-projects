/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:56:28 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/12 03:44:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_is_in_set(char c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	len;

	start = 0;
	len = ft_strlen(s1);
	while (ft_char_is_in_set(s1[start], set))
		start++;
	while (len > start && ft_char_is_in_set(s1[len - 1], set))
		len--;
	return (ft_substr(s1, start, len - start));
}
