/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 02:21:04 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/12 02:25:21 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_len_word(const char *str, int *index, char c, int *i)
{
	size_t	j;
	size_t	len;

	len = -1;
	while (str[*index] && str[*index] == c)
		(*index)++;
	while (str[*index + ++len] && str[*index + len] != c)
	{
		j = (*index) + len;
		avoid_quote(str, &j);
		len = len + j - (*index) - len;
	}
	i[1] = len;
	i[0] = -1;
	return (0);
}

static char	*ft_get_next_words(t_memory_table *mem, int *index,
const char *str, char c)
{
	int		i[2];
	char	*res;

	count_len_word(str, index, c, i);
	res = gc_malloc(mem, (i[1] + 1) * sizeof(char));
	while (++i[0] < i[1])
	{
		res[i[0]] = str[*index];
		*index = *index + 1;
	}
	res[i[0]] = '\0';
	return (res);
}

static int	ft_count_words(const char *str, char c)
{
	size_t			i;
	int				words;
	const size_t	len = ft_strlen(str);

	words = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (i <= len && str[i])
	{
		avoid_quote(str, &i);
		if (i <= len && str[i] && str[i] != c)
		{
			words++;
			while (i <= len && str[i] && str[i] != c)
			{
				avoid_quote(str, &i);
				i++;
			}
		}
		if (i <= len && str[i])
			i++;
	}
	return (words);
}

char	**split_parse(t_memory_table *mem, const char *s, char c)
{
	int		i;
	int		j;
	int		cw;
	char	**res;

	i = 0;
	j = 0;
	cw = ft_count_words(s, c);
	res = gc_malloc(mem, (cw + 1) * sizeof(char *));
	while (i < cw)
	{
		res[i] = ft_get_next_words(mem, &j, s, c);
		i++;
	}
	res[i] = 0;
	return (res);
}
