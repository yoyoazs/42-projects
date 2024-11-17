/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:48:44 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/04 11:01:27 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_add_quote(t_memory_table *mem, char **var, size_t *i,
char *quote)
{
	size_t	len;
	char	*tmp;

	len = 0;
	(*quote) = 0;
	(*i) = -1;
	while ((*var)[++(*i)])
	{
		if ((*var)[(*i)] == '\'' || (*var)[(*i)] == '"')
			len++;
		len++;
	}
	tmp = gc_malloc(mem, sizeof(char) * (len + 1));
	tmp[len] = 0;
	(*i) = -1;
	return (tmp);
}

void	add_quote(t_memory_table *mem, char **var)
{
	size_t	len;
	size_t	i;
	char	*tmp;
	char	quote;

	tmp = set_add_quote(mem, var, &i, &quote);
	len = 0;
	while ((*var)[++i])
	{
		if (((*var)[i] == '\'' || (*var)[i] == '"') && !quote)
		{
			tmp[len++] = '"';
			quote = (*var)[i];
		}
		else if ((*var)[i] == quote)
		{
			quote = 0;
			tmp[len++] = (*var)[i];
			tmp[len++] = '"';
			continue ;
		}
		tmp[len++] = (*var)[i];
	}
	gc_free(mem, (*var));
	(*var) = tmp;
}
