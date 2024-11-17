/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:17:08 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:44:36 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "pipex.h"

static int	msg_no_arg(t_cmd *cmd)
{
	ft_putstr_fd("minishell: no arguments and no options expected\n", 2);
	return (cmd->ret = 1);
}

int	run_env(char **env, int *fds, char **argv, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (argv && argv[0] && argv[1])
		return (msg_no_arg(cmd));
	if (!env[0])
	{
		ft_putstr_fd("minishell: no Environment Variables\n", 2);
		return (cmd->ret = 1);
	}
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			write(fds[1], env[i], ft_strlen(env[i]));
			if (write(fds[1], "\n", 1) == -1)
				return (file_is_full(argv[0], cmd));
		}
	}
	return (cmd->ret = 0);
}
