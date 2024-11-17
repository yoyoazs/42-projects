/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:15:16 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:42:05 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chld_prcss(t_cmd *cmd, int *fds, char ***env)
{
	int	i;

	i = 0;
	if (cmd->ac == 1)
		exec_last(cmd, fds, env);
	else if (cmd->ac > 1)
	{
		while (i < cmd->ac - 1)
		{
			exec_middle_one_cmd(cmd, fds, i, env);
			i++;
		}
		exec_last(cmd, fds, env);
	}
	closefds(fds);
	i--;
	while (i >= 0)
		waitpid(cmd->pids[i--], NULL, 0);
}

int	pipex(char **argv, t_cmd *cmd, char ***env)
{
	int		fds[2];

	cut_cmd_n_paths(*env, cmd, argv, cmd->ac);
	if (pipe(fds) == -1)
	{
		cmd->pb = error_pipe(cmd, -1);
		return (cmd->ret = cmd->pb);
	}
	crossing_craft_doc(cmd, env);
	if (cmd->pb == 1)
		return (cmd->ret = 1);
	if (cmd->pb == 130)
		return (cmd->ret = pb_hd(cmd, fds));
	if (cmd->ac == 1 && ft_strlen(argv[0]) == 0)
		return (cmd->ret = without_cmd(cmd, fds));
	if (cmd->ac == 1 && builtin_test_one(0, cmd, fds, env))
		return (free_paths_rightpaths_cut(cmd), cmd->ret);
	chld_prcss(cmd, fds, env);
	return (wait_commands(cmd, fds));
}

int	pipex_exec(t_data_ms *data, int argc, char **argv, char ***env)
{
	t_cmd	cmd;

	cmd.mem = data->mem;
	cmd.ac = argc;
	cmd.pb = -1;
	cmd.tmp = -1;
	cmd.int_out = 1;
	cmd.int_in = 0;
	cmd.change_in = 0;
	cmd.change_out = 0;
	cmd.std = &data->std;
	cmd.pids = gc_malloc(cmd.mem, (cmd.ac + 1) * sizeof(pid_t));
	cmd.alias = &data->alias;
	cmd.ret = 0;
	cmd.ret = pipex(argv, &cmd, env);
	gc_free(data->mem, cmd.pids);
	return (cmd.ret);
}
