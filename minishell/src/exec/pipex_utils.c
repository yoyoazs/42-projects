/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:01:51 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:41:15 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	pb_hd(t_cmd *cmd, int *fds)
{
	delete_hd_file(cmd);
	free_paths_rightpaths_cut(cmd);
	closefds(fds);
	return (cmd->ret = 130);
}

int	hd_ctrld_msg(char *eof, t_cmd *cmd)
{
	write(2, "\nminishell: warning: here-document ", 35);
	write(2, "delimited by end-of-file (wanted `", 34);
	write(2, eof, ft_strlen(eof));
	write(2, "')\n", 3);
	return (cmd->ret = 0);
}

int	access_test(int num, t_cmd *cmd, int *fds, int tmp)
{
	struct stat	path_stat;

	if (stat((cmd->cut)[num][0], &path_stat) != 0)
		return (1);
	if ((cmd->cut)[num][0] == NULL || S_ISDIR(path_stat.st_mode))
	{
		if (tmp != -1)
			close(tmp);
		if (S_ISDIR(path_stat.st_mode))
			message_command_fail_n_free_dir((cmd->cut)[num][0], fds);
		else
			message_command_fail_n_free((cmd->cut)[num][0], fds);
		return (1);
	}
	if (access((cmd->cut)[num][0], R_OK | X_OK) == 0)
	{
		cmd->right_path[num] = ft_strdup((const char *)(cmd->cut)[num][0]);
		if (cmd->right_path[num] == NULL)
			return (1);
		return (0);
	}
	else
		return (1);
}

int	verif_last(t_cmd *cmd, t_std *stack)
{
	int	tmp;

	tmp = stack->in;
	stack = stack->next;
	while (stack)
	{
		if (!tmp)
		{
			if (!stack->in && stack->number == cmd->op_nb)
				return (0);
		}
		else
		{
			if (stack->in && stack->number == cmd->op_nb)
				return (0);
		}
		stack = stack->next;
	}
	return (1);
}

int	wait_commands(t_cmd *cmd, int *fds)
{
	int	status;
	int	ret;

	closefds(fds);
	if (cmd->int_in > 0)
		close(cmd->int_in);
	free_paths_rightpaths_cut(cmd);
	while (errno != ECHILD)
	{
		if (waitpid(cmd->pids[cmd->ac - 1], &status, 0)
			== cmd->pids[cmd->ac - 1])
		{
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			else
				ret = 128 + WTERMSIG(status);
		}
	}
	delete_hd_file(cmd);
	return (ret);
}
