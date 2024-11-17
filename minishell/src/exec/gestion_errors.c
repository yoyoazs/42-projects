/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 19:30:05 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:48:29 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	error(char *msg, t_cmd *cmd, int *fds, int tmp)
{
	closefds(fds);
	if (tmp != -1)
		close(tmp);
	perror(msg);
	free_paths_rightpaths_cut(cmd);
	delete_hd_file(cmd);
	return (cmd->ret = 1);
}

int	error_pipe(t_cmd *cmd, int tmp)
{
	perror("minishell: pipe");
	if (tmp != -1)
		close(tmp);
	free_paths_rightpaths_cut(cmd);
	delete_hd_file(cmd);
	return (cmd->ret = 1);
}

int	error_exec(t_cmd *cmd, int *fds)
{
	perror("minishell: execve");
	free_paths_rightpaths_cut(cmd);
	closefds(fds);
	return (cmd->ret = 1);
}

int	error_existence(char *name, t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	write(2, name, ft_strlen(name));
	write(2, ": No such file or directory\n", 29);
	return (cmd->ret = 1);
}

int	error_permission(char *inf, char *outf, char *name, t_cmd *cmd)
{
	write(2, "minishell: ", 11);
	if (outf != NULL)
	{
		if (access(inf, F_OK) != 0)
		{
			write(2, outf, ft_strlen(outf));
			write(2, ": Permission denied\n", 21);
			error_existence(name, cmd);
		}
		else if (access(inf, R_OK) != 0)
		{
			write(2, inf, ft_strlen(inf));
			write(2, ": Permission denied\n", 21);
		}
		write(2, outf, ft_strlen(outf));
		write(2, ": Permission denied\n", 21);
	}
	else
	{
		write(2, inf, ft_strlen(inf));
		write(2, ": Permission denied\n", 21);
		return (cmd->ret = 1);
	}
	return (cmd->ret = 1);
}
