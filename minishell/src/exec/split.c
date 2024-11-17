/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:02:08 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/04 08:56:03 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static int	ft_gnw_extension(int *index, const char *str, int *i, char *quote)
{
	if (str[*index] == (*quote))
	{
		(*quote) = 0;
		i[0] = i[0] - 1;
		i[1] = i[1] - 1;
		return (0);
	}
	else if ((str[*index] == '\'' || str[*index] == '"') && (*quote) == 0)
	{
		(*quote) = str[*index];
		i[0] = i[0] - 1;
		i[1] = i[1] - 1;
		return (0);
	}
	return (1);
}

static char	*ft_get_next_words(t_memory_table *mem, int *index,
const char *str, char c)
{
	int		i[2];
	char	*res;
	char	quote;

	quote = 0;
	count_len_word(str, index, c, i);
	res = gc_malloc(mem, (i[1] + 1) * sizeof(char));
	while (++i[0] < i[1])
	{
		if (ft_gnw_extension(index, str, i, &quote) && str[*index] != quote)
			res[i[0]] = str[*index];
		*index = *index + 1;
	}
	res[i[0]] = '\0';
	return (res);
}

static int	ft_count_words(const char *str, char c)
{
	size_t	i;
	int		words;
	char	quote;

	words = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			words++;
			while (str[i] && (str[i] != c || quote))
			{
				if ((str[i] == '"' || str[i] == '\'') && quote == 0)
					quote = str[i];
				else if ((str[i] == '"' || str[i] == '\'') && quote == str[i])
					quote = 0;
				i++;
			}
		}
	}
	return (words);
}

char	**split(t_memory_table *mem, const char *s, char c)
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
	i = -1;
	return (res);
}
