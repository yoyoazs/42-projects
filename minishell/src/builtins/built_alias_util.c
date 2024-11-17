/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_alias_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:47:56 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:44:05 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	show_all_alias(t_cmd *cmd, int *fds)
{
	t_alias	*current;

	current = (*cmd->alias);
	while (current)
	{
		ft_putstr_fd("alias ", fds[1]);
		ft_putstr_fd(current->name, fds[1]);
		ft_putstr_fd("='", fds[1]);
		ft_putstr_fd(current->command, fds[1]);
		if (write(fds[1], "'\n", 2) == -1)
			return (file_is_full("alias", cmd));
		current = current->next;
	}
	return (cmd->ret = 0);
}

int	show_alias(t_cmd *cmd, char *alias, int *fds)
{
	t_alias	*current;

	current = (*cmd->alias);
	while (current)
	{
		if (ft_strcmp(current->name, alias) == 0)
		{
			ft_putstr_fd("alias ", 1);
			ft_putstr_fd(current->name, 1);
			ft_putstr_fd("='", 1);
			ft_putstr_fd(current->command, 1);
			if (write(fds[1], "'\n", 2) == -1)
				return (file_is_full("alias", cmd));
			return (cmd->ret = 0);
		}
		current = current->next;
	}
	ft_putstr_fd("minishell: alias: ", 2);
	ft_putstr_fd(alias, 2);
	ft_putstr_fd(": not found\n", 2);
	return (cmd->ret = 1);
}
