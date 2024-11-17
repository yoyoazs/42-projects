/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildings.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:51:34 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:47:46 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "pipex.h"

int	builtin_cmd(int num, t_cmd *cmd, int *fds, char ***env)
{
	if ((cmd->cut)[num] == NULL)
		return (0);
	if (ft_strncmp("echo", (cmd->cut)[num][0], 10) == 0)
		run_echo(cmd->cut[num], fds, cmd);
	else if (ft_strncmp("pwd", (cmd->cut)[num][0], 10) == 0)
		run_pwd(fds, cmd->cut[num], cmd);
	else if (ft_strncmp("cd", (cmd->cut)[num][0], 10) == 0)
		run_cd(cmd, cmd->cut[num], env);
	else if (ft_strncmp("exit", (cmd->cut)[num][0], 10) == 0)
		run_exit((cmd->cut)[num], cmd, fds);
	else if (ft_strncmp("unset", (cmd->cut)[num][0], 10) == 0)
		run_unset((cmd->cut)[num], env, cmd);
	else if (ft_strncmp("export", (cmd->cut)[num][0], 10) == 0)
		run_export(cmd, env, (cmd->cut)[num], fds);
	else if (ft_strncmp("env", (cmd->cut)[num][0], 10) == 0)
		run_env(*env, fds, (cmd->cut)[num], cmd);
	else if (ft_strncmp("alias", (cmd->cut)[num][0], 10) == 0)
		run_alias(cmd, (cmd->cut)[num], fds);
	else
		return (0);
	close_exit_exec(cmd, fds, 0);
	return (1);
}

int	builtin_test_one(int num, t_cmd *cmd, int *fds, char ***env)
{
	if ((cmd->cut)[num][0] == NULL)
		return (1);
	if (!(ft_strncmp("echo", (cmd->cut)[num][0], 10) && ft_strncmp("pwd",
		(cmd->cut)[num][0], 10) && ft_strncmp("cd", (cmd->cut)[num][0], 10)
		&& ft_strncmp("exit", (cmd->cut)[num][0], 10) && ft_strncmp("unset",
		(cmd->cut)[num][0], 10) && ft_strncmp("export", (cmd->cut)[num][0], 10)
		&& ft_strncmp("env", (cmd->cut)[num][0], 10)
		&& ft_strncmp("alias", (cmd->cut)[num][0], 10)))
	{
		open_file(cmd, 0);
		if (cmd->pb != -1)
			return (cmd->ret = 1);
		if ((*cmd->std)->next->next && (*cmd->std)->next->next->lim)
			unlink((*cmd->std)->next->next->name);
		if (cmd->change_out)
		{
			close(fds[1]);
			fds[1] = cmd->int_out;
		}
		return (builtin_cmd(num, cmd, fds, env));
	}
	else
		return (0);
}

int	without_cmd(t_cmd *cmd, int *fds)
{
	open_file(cmd, 0);
	delete_hd_file(cmd);
	free_paths_rightpaths_cut(cmd);
	closefds(fds);
	if (cmd->change_out > 0)
		close(cmd->int_out);
	if (cmd->pb != -1)
		return (cmd->ret = 1);
	else
		return (cmd->ret = 0);
}

int	file_is_full(char *to_write, t_cmd *cmd)
{
	if (!ft_strcmp(to_write, "env"))
	{
		write(2, "env: write error: No space left on device\n", 42);
		return (cmd->ret = 125);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, to_write, ft_strlen(to_write));
		write(2, ": write error: No space left on device\n", 39);
		return (cmd->ret = 1);
	}
}
