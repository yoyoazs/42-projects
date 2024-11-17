/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:21:44 by npigeon           #+#    #+#             */
/*   Updated: 2024/08/19 15:07:44 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	message_command_fail_n_free_dir(char *prog_name, int *fds)
{
	write(2, "minishell: ", 12);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": Is a directory\n", 18);
	closefds(fds);
	gc_exit(126);
}

void	message_command_fail_n_free(char *prog_name, int *fds)
{
	write(2, "minishell: ", 12);
	write(2, prog_name, ft_strlen(prog_name));
	write(2, ": command not found\n", 20);
	closefds(fds);
	gc_exit(127);
}

void	closefds(int *fds)
{
	if (fds[1] >= 0)
		close(fds[1]);
	if (fds[0] >= 0)
		close(fds[0]);
}
