/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 08:32:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/05 17:36:59 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_alias(t_cmd *cmd, char **argv, int *fds)
{
	t_alias	*new_alias;
	int		i;

	if (!argv[1])
	{
		if (show_all_alias(cmd, fds) == 1)
			return (1);
	}
	i = 0;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '=') == NULL)
		{
			if (show_alias(cmd, argv[i], fds) == 1)
				return (1);
			continue ;
		}
		new_alias = (t_alias *)gc_malloc(cmd->mem, sizeof(t_alias));
		new_alias->name = gc_strdup(cmd->mem, ft_strtok(argv[i], "="));
		new_alias->command = gc_strdup(cmd->mem, ft_strtok(NULL, "\0"));
		new_alias->next = NULL;
		new_alias->next = (*cmd->alias);
		(*cmd->alias) = new_alias;
	}
	return (cmd->ret = 0);
}

static int	is_resolved_alias(t_alias *resolved_alias, char *name)
{
	t_alias	*tmp;

	tmp = resolved_alias;
	while (tmp)
	{
		if (ft_strcmp(tmp->command, name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static char	*strdup_without_space(t_memory_table *mem, char *str, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	(*i) = 0;
	if (str[0] == ' ')
		j++;
	while (str[(*i) + j] && str[(*i) + j] != ' ')
		(*i)++;
	tmp = gc_strndup(mem, str + j, (*i));
	(*i) += j;
	return (tmp);
}

static char	*get_cmd_alias_loop(t_data_ms *data, t_alias **tmp_alias,
t_alias **resolved_alias, char *cmd)
{
	char	*tmp;
	char	*cmd_tmp;
	int		i;
	t_alias	*current;

	current = data->alias;
	cmd_tmp = strdup_without_space(data->mem, cmd, &i);
	while (current && current->name)
	{
		if (ft_strcmp(current->name, cmd_tmp) == 0
			&& !is_resolved_alias(*resolved_alias, current->name))
		{
			(*tmp_alias) = gc_malloc(data->mem, sizeof(t_alias));
			(*tmp_alias)->command = gc_strdup(data->mem, current->name);
			(*tmp_alias)->next = (*resolved_alias);
			(*resolved_alias) = (*tmp_alias);
			tmp = gc_strdup(data->mem, current->command);
			tmp = gc_strjoin(data->mem, tmp, cmd + i);
			gc_free(data->mem, cmd_tmp);
			return (get_command_alias(data, tmp));
		}
		current = current->next;
	}
	gc_free(data->mem, cmd_tmp);
	return (cmd);
}

char	*get_command_alias(t_data_ms *data, char *cmd)
{
	static t_alias	*resolved_alias = NULL;
	t_alias			*tmp_alias;

	tmp_alias = NULL;
	cmd = get_cmd_alias_loop(data, &tmp_alias, &resolved_alias, cmd);
	if (resolved_alias == NULL)
		return (cmd);
	tmp_alias = resolved_alias->next;
	while (resolved_alias)
	{
		gc_free(data->mem, resolved_alias->command);
		gc_free(data->mem, resolved_alias);
		resolved_alias = tmp_alias;
		if (resolved_alias)
			tmp_alias = resolved_alias->next;
	}
	return (cmd);
}
