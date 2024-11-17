/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:27:16 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/08 15:18:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_tilde(t_memory_table *mem, char **env, char **cmd, size_t *i)
{
	char	*home;
	char	*tmp;

	if ((*i == 0 || (*cmd)[(*i) - 1] == ' ') && ((*cmd)[(*i) + 1] == ' '
		|| (*cmd)[(*i) + 1] == '\0' || (*cmd)[(*i) + 1] == '/'))
	{
		home = get_env_var(mem, env, "HOME");
		if (!home)
			home = gc_strdup(mem, "");
		tmp = gc_strndup(mem, (*cmd), *i);
		tmp = gc_strjoin(mem, tmp, home);
		tmp = gc_strjoin(mem, tmp, (*cmd) + *i + 1);
		gc_free(mem, (*cmd));
		gc_free(mem, home);
		(*cmd) = tmp;
	}
}

t_mem_and_cmd	*set_mem_info(t_memory_table *mem, long int cmd)
{
	t_mem_and_cmd	*tmp;

	tmp = gc_malloc(mem, sizeof(t_mem_and_cmd));
	tmp->cmd = cmd;
	tmp->mem = mem;
	return (tmp);
}

void	expand(t_data_ms *data, char **env, char **subcommand)
{
	size_t			i;
	int				single_quote;
	int				double_quote;
	t_mem_and_cmd	*info;

	single_quote = 0;
	double_quote = 0;
	i = -1;
	info = set_mem_info(data->mem, data->cmd);
	while (++i <= ft_strlen((*subcommand)) && (*subcommand)[i])
	{
		if ((*subcommand)[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if ((*subcommand)[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (!single_quote && (*subcommand)[i] == '$')
			handle_dollar(info, env, subcommand, &i);
		else if (!double_quote && !single_quote && (*subcommand)[i] == '~')
			handle_tilde(data->mem, env, subcommand, &i);
		else if (!double_quote && !single_quote && ((*subcommand)[i] == '*'
			|| (*subcommand)[i] == '?'))
			handle_wildcard(data->mem, data->mem_ps, subcommand, &i);
	}
	gc_free(data->mem, info);
}
