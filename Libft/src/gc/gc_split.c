/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:34:22 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/11/14 10:51:16 by ybeaucou         ###   ########.fr       */
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

char	**gc_split(t_memory_table *mem, char const *str, char charset)
{
	char	**split;
	size_t	start;
	size_t	end;
	int		i;

	split = gc_malloc(mem, sizeof(char *) * (ft_count_words(str, charset) + 1));
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
		split[i] = gc_substr(mem, str, start, (end - start));
		start = end;
		i++;
	}
	split[i] = 0;
	return (split);
}

char	*gc_substr(t_memory_table *mem, char const *s, unsigned int start,
size_t len)
{
	char	*str2;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
		return (gc_strdup(mem, ""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str2 = (char *)gc_malloc(mem, len + 1);
	if (str2 == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		str2[i] = s[i + start];
	str2[len] = '\0';
	return (str2);
}
