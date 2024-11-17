/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cut_find_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:03:47 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/04 08:56:02 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cut_paths(char **env, t_cmd *cmd)
{
	char	*path_variable;
	int		i;

	cmd->paths = NULL;
	path_variable = NULL;
	i = -1;
	while (env[++i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 4) == 0 && ft_strlen(env[i]) >= 5)
			path_variable = env[i] + 5;
	}
	if (path_variable == NULL)
		return ;
	cmd->paths = split(cmd->mem, path_variable, ':');
	if (cmd->paths == NULL && path_variable != NULL)
	{
		free_paths_rightpaths(cmd);
		return ;
	}
}

void	error_cut_cmd(t_cmd *cmd, int i)
{
	int	j;

	j = -1;
	while (--i >= 0)
	{
		while ((cmd->cut)[i][++j])
			gc_free(cmd->mem, (cmd->cut)[i][j]);
		gc_free(cmd->mem, (cmd->cut)[i]);
		j = -1;
	}
	gc_free(cmd->mem, (cmd->cut));
	free_paths_rightpaths(cmd);
	return ;
}

void	cut_cmds(t_cmd *cmd, char **argv, int argc)
{
	int	i;

	i = -1;
	cmd->cut = gc_malloc(cmd->mem, (argc + 1) * sizeof(char *));
	while (++i < argc)
	{
		if (argv[i] == NULL)
		{
			(cmd->cut)[i] = gc_strdup(cmd->mem, argv[i]);
			continue ;
		}
		(cmd->cut)[i] = split(cmd->mem, argv[i], ' ');
	}
	(cmd->cut)[i] = NULL;
}

void	cut_cmd_n_paths(char **env, t_cmd *cmd, char **argv, int ac)
{
	cmd->right_path = gc_malloc(cmd->mem, (ac + 1) * sizeof(char *));
	cut_paths(env, cmd);
	cut_cmds(cmd, argv, ac);
	return ;
}

void	find_cmd_paths(t_cmd *cmd, int num, int *fds)
{
	int		i;
	char	*temp;

	if (((cmd->cut)[num][0][0] == '.'
		|| (cmd->cut)[num][0][0] == '/')
		&& access_test(num, cmd, fds, cmd->tmp) == 0)
		return ;
	i = -1;
	temp = gc_strjoin(cmd->mem, gc_strdup(cmd->mem, "/"), (cmd->cut)[num][0]);
	if (!temp)
		error("minishell: ft_strjoin", cmd, fds, cmd->tmp);
	while (cmd->paths && (cmd->paths)[++i])
	{
		(cmd->right_path)[num] = gc_strjoin(cmd->mem, (cmd->paths)[i], temp);
		if (!(cmd->right_path)[num])
			error("minishell: ft_strjoin", cmd, fds, cmd->tmp);
		if (access((cmd->right_path)[num], X_OK) == 0)
			return (gc_free(cmd->mem, temp));
		else
			gc_free(cmd->mem, (cmd->right_path)[num]);
	}
	gc_free(cmd->mem, temp);
	if (cmd->tmp != -1)
		close(cmd->tmp);
	message_command_fail_n_free((cmd->cut)[num][0], fds);
}
