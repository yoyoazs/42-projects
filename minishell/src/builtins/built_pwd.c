/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:34:39 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:44:50 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "pipex.h"

int	run_pwd(int *fds, char **av, t_cmd *cmd)
{
	char	buffer[1024];
	char	*pwd;

	pwd = getcwd(buffer, sizeof(buffer));
	if (pwd == NULL)
	{
		perror("minishell: getcwd() error");
		return (cmd->ret = 1);
	}
	write(fds[1], pwd, ft_strlen(pwd));
	if (write(fds[1], "\n", 1) == -1)
		return (file_is_full(av[0], cmd));
	return (0);
}
