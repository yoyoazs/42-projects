/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 20:17:55 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/06/01 12:43:46 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const*str, char charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (*str)
	{
		if (*str != charset && words == 0)
		{
			words = 1;
			i++;
		}
		else if (*str == charset)
			words = 0;
		str++;
	}
	return (i);
}

char	**ft_split(char const *str, char charset)
{
	char	**split;
	size_t	start;
	size_t	end;
	int		i;

	split = malloc(sizeof(char *) * (ft_count_words(str, charset) + 1));
	if (!split)
		return (0);
	start = 0;
	end = 0;
	i = 0;
	while (ft_count_words(str, charset) > i)
	{
		while (str[start] == charset)
			start++;
		end = start;
		while (str[end] != charset && str[end])
			end++;
		split[i] = ft_substr(str, start, (end - start));
		start = end;
		i++;
	}
	split[i] = 0;
	return (split);
}
