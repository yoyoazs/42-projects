/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:05:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 10:28:54 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	display_exported_vars(char **env, int *fds, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		write(fds[1], "export ", 7);
		write(fds[1], env[i], ft_strlen(env[i]));
		if (write(fds[1], "\n", 1) == -1)
			return (file_is_full("export", cmd));
	}
	return (cmd->ret = 0);
}

static void	realloc_env(char ***env, char *argv, t_memory_table *table)
{
	char	**new_env;
	int		i;
	int		j;

	j = -1;
	i = 0;
	while ((*env)[i])
		i++;
	new_env = gc_calloc(table, sizeof(char *), i + 2);
	while (++j < i)
		new_env[j] = (*env)[j];
	new_env[i] = gc_strdup(table, argv);
	new_env[i + 1] = NULL;
	gc_free(table, *env);
	*env = new_env;
}

void	key_n_value(t_cmd *cmd, char *delim, char *argv, char ***env)
{
	char	*key;
	char	*value;

	if (delim)
	{
		key = gc_strndup(cmd->mem, argv, (size_t)(delim - argv));
		value = gc_strdup(cmd->mem, delim);
	}
	else
	{
		key = gc_strdup(cmd->mem, argv);
		value = gc_strdup(cmd->mem, "");
	}
	if (var_exist(*env, key) == -1)
	{
		realloc_env(env, argv, cmd->mem);
		gc_free(cmd->mem, key);
	}
	else
		change_var(env, key, value, cmd->mem);
	gc_free(cmd->mem, value);
}

int	run_export(t_cmd *cmd, char ***env, char **argv, int *fds)
{
	char	*delimiter;
	int		i;
	int		size;

	i = 0;
	cmd->ret = 0;
	while (argv[++i])
	{
		delimiter = ft_strchr(argv[i], '=');
		size = ft_strlen(argv[i]) - ft_strlen(delimiter);
		if ((!ft_isalpha(argv[i][0]) && argv[i][0] != '_')
			|| !str_is_alphanum(argv[i], size))
		{
			cmd->ret = 1;
			write(2, "export : '", 10);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
			key_n_value(cmd, delimiter, argv[i], env);
	}
	if (!argv[1])
		return (display_exported_vars(*env, fds, cmd));
	return (cmd->ret);
}
