/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:02:02 by npigeon           #+#    #+#             */
/*   Updated: 2024/04/23 12:02:02 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 1;
	if (!ft_strncmp("-", str, 1))
	{
		while (str[i])
		{
			if (ft_strncmp("n", str + i, 1))
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	run_echo(char **av, int *fds, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (av && !av[i])
		return (write(fds[1], "\n", 1), 0);
	while (av[i] && !check_n(av[i]))
		i++;
	while (av[i])
	{
		if (write(fds[1], av[i], ft_strlen(av[i])) == -1)
			return (file_is_full(av[0], cmd));
		if (av[i + 1])
			write(fds[1], " ", 1);
		i++;
	}
	if (check_n(av[1]) == 0)
		return (cmd->ret = 0);
	else
	{
		if (write(fds[1], "\n", 1) == -1)
			return (file_is_full(av[0], cmd));
		return (cmd->ret = 0);
	}
}
