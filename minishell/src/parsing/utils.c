/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:26:27 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 09:51:53 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(t_memory_table *mem, char **tab)
{
	int	i;

	if (!tab || !mem)
		return ;
	i = -1;
	while (tab[++i])
	{
		if (tab[i])
			gc_free(mem, tab[i]);
	}
	gc_free(mem, tab);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token_start;

	if (str != NULL)
		last_token = str;
	else
	{
		if (last_token == NULL)
			return (NULL);
		while (*last_token != '\0' && ft_strchr(delim, *last_token) != NULL)
			last_token++;
	}
	if (*last_token == '\0')
		return (NULL);
	token_start = last_token;
	while (*last_token != '\0' && ft_strchr(delim, *last_token) == NULL)
		last_token++;
	if (*last_token != '\0')
	{
		*last_token = '\0';
		last_token++;
	}
	return (token_start);
}

bool	is_sep_not_pipe(t_parser *p)
{
	return (p->current->type == TOKEN_SEPARATOR
		&& !(p->current->value[0] == '|' && !p->current->value[1]));
}

t_parser	*init_parser(t_data_ms *data, t_token *tokens)
{
	t_parser		*parse;

	parse = gc_malloc(data->mem, sizeof(t_parser));
	parse->cmds = NULL;
	parse->in_bracket = 0;
	parse->current = tokens;
	parse->number = 0;
	parse->cmds = create_commands(data);
	parse->current_scmd = parse->cmds->subcommands;
	parse->last_cmd = parse->cmds;
	return (parse);
}
