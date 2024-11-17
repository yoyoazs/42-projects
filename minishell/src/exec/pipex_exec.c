/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:06:53 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:40:55 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

void	execution_cmd_or_builtins(t_cmd *cmd, int *fds, char ***env, int num)
{
	if (!(cmd->cut)[num])
		return ;
	if (builtin_cmd(num, cmd, fds, env))
	{
		close(cmd->tmp);
		gc_exit(cmd->ret);
	}
	find_cmd_paths(cmd, num, fds);
	closefds(fds);
	close(cmd->tmp);
	execve((cmd->right_path)[num], (cmd->cut)[num], *env);
	error_exec(cmd, fds);
}

int	redirection(t_cmd *cmd, int *fds)
{
	if (dup2(cmd->tmp, STDIN_FILENO) == -1)
		return (error("minishell: dup2", cmd, fds, cmd->tmp));
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (error("minishell: dup2", cmd, fds, cmd->tmp));
	return (0);
}

void	close_exit_exec(t_cmd *cmd, int *fds, int exit)
{
	closefds(fds);
	if (cmd->change_in > 0)
		close(cmd->int_in);
	if (cmd->change_out > 0)
		close(cmd->int_out);
	if (exit)
	{
		close(cmd->tmp);
		gc_exit(cmd->ret = 1);
	}
}

void	exec_middle_one_cmd(t_cmd *cmd, int *fds, int i, char ***env)
{
	cmd->tmp = dup(fds[0]);
	closefds(fds);
	if (pipe(fds) == -1)
		error_pipe(cmd, cmd->tmp);
	cmd->pids[i] = fork();
	if (cmd->pids[i] == -1)
		error("minishell: fork", cmd, fds, cmd->tmp);
	else if (cmd->pids[i] == 0)
	{
		close(fds[0]);
		open_file(cmd, i);
		if (cmd->pb != -1)
			close_exit_exec(cmd, fds, 1);
		if (cmd->change_in && !close(cmd->tmp))
			cmd->tmp = cmd->int_in;
		if (cmd->change_out && !close(fds[1]))
			fds[1] = cmd->int_out;
		if ((cmd->cut)[i] && (cmd->cut)[i][0] && !redirection(cmd, fds))
			execution_cmd_or_builtins(cmd, fds, env, i);
		else
			close_exit_exec(cmd, fds, 1);
	}
	close(cmd->tmp);
}

void	exec_last(t_cmd *cmd, int *fds, char ***env)
{
	cmd->tmp = dup(fds[0]);
	closefds(fds);
	if (pipe(fds) == -1)
		error_pipe(cmd, cmd->tmp);
	cmd->pids[cmd->ac - 1] = fork();
	if (cmd->pids[cmd->ac - 1] == -1)
		error("minishell: fork", cmd, fds, cmd->tmp);
	else if (cmd->pids[cmd->ac - 1] == 0)
	{
		close(fds[1]);
		open_file(cmd, cmd->ac - 1);
		if (cmd->pb != -1)
			close_exit_exec(cmd, fds, 1);
		if (cmd->change_in && !close(cmd->tmp))
			cmd->tmp = cmd->int_in;
		if (cmd->change_out)
			fds[1] = cmd->int_out;
		if ((cmd->cut)[cmd->ac - 1] && (cmd->cut)[cmd->ac - 1][0]
			&& !redirection(cmd, fds))
			execution_cmd_or_builtins(cmd, fds, env, cmd->ac - 1);
		else
			close_exit_exec(cmd, fds, 1);
	}
	close(cmd->tmp);
}
