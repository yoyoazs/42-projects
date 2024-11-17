/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 21:11:54 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/12 01:09:51 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_completion_cmd(t_readline *rl, char **cmds, int count,
char *prefix)
{
	char	*tmp;
	int		i;
	size_t	new_len;

	i = 0;
	if (count == 1)
	{
		new_len = ft_strlen(cmds[0]) + ft_strlen(rl->input)
			- ft_strlen(prefix) + 1;
		if (rl->max_len_input < new_len)
			realloc_input_cmd(rl, cmds);
		tmp = gc_malloc(rl->mem, rl->max_len_input);
		while (rl->input[i] == ' ')
			i++;
		ft_strlcpy(tmp, rl->input, i + 1);
		ft_strlcat(tmp, cmds[0], rl->max_len_input);
		if (rl->input[ft_strlen(prefix) + i])
			ft_strlcat(tmp, rl->input + ft_strlen(prefix) + i,
				rl->max_len_input);
		gc_free(rl->mem, rl->input);
		rl->input = tmp;
		rl->index = i + ft_strlen(cmds[0]);
	}
	else if (count > 1)
		print_cmd_list(rl, cmds, count);
}

static char	*get_prefix_cmd(t_readline *rl)
{
	int	i;
	int	len;

	i = rl->index;
	while (i > 0 && rl->input[i - 1] != ' ')
		i--;
	len = 0;
	while (rl->input[i + len] && rl->input[i + len] != ' ')
		len++;
	return (gc_strndup(rl->mem, rl->input + i, len));
}

static void	get_cmd(t_readline *rl, DIR *dir, char ***cmds, int *count)
{
	struct dirent	*entry;
	char			*prefix;
	char			**tmp;

	prefix = get_prefix_cmd(rl);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strncmp(entry->d_name, prefix, ft_strlen(prefix)) == 0)
		{
			if (!is_in_command_list(entry->d_name, *cmds, *count))
			{
				tmp = *cmds;
				*cmds = gc_malloc(rl->mem, sizeof(char *) * ((*count) + 2));
				ft_memcpy(*cmds, tmp, sizeof(char *) * (*count));
				(*cmds)[(*count)] = gc_strdup(rl->mem, entry->d_name);
				(*count)++;
				(*cmds)[*count] = NULL;
				gc_free(rl->mem, tmp);
			}
		}
		entry = readdir(dir);
	}
	gc_free(rl->mem, prefix);
}

static void	get_all_cmds(t_readline *rl, char *path_env, char ***cmds,
int *count)
{
	char	*token;
	DIR		*dir;

	token = ft_strtok(path_env, ":");
	*cmds = gc_malloc(rl->mem, sizeof(char *));
	while (token != NULL)
	{
		dir = opendir(token);
		if (dir == NULL)
		{
			token = ft_strtok(NULL, ":");
			continue ;
		}
		get_cmd(rl, dir, cmds, count);
		closedir(dir);
		token = ft_strtok(NULL, ":");
	}
}

void	complete_command(t_readline *rl)
{
	char	*prefix;
	char	*path_env;
	char	**all_commands;
	int		count;
	int		i;

	count = 0;
	prefix = get_prefix_cmd(rl);
	i = -1;
	path_env = get_env_var(rl->mem, rl->env, "PATH");
	get_all_cmds(rl, path_env, &all_commands, &count);
	execute_completion_cmd(rl, all_commands, count, prefix);
	while (++i < count)
		gc_free(rl->mem, all_commands[i]);
	gc_free(rl->mem, all_commands);
	gc_free(rl->mem, prefix);
	gc_free(rl->mem, path_env);
}
