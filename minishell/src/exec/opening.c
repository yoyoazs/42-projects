/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 09:11:35 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:49:16 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	op_in(t_cmd *cmd, t_std *current)
{
	if (access(current->name, F_OK) != 0)
	{
		cmd->pb = error_existence(current->name, cmd);
		return (-1);
	}
	if (access(current->name, R_OK) != 0)
	{
		cmd->pb = error_permission(current->name, NULL, current->name, cmd);
		return (-1);
	}
	else if (verif_last(cmd, current))
	{
		if (cmd->int_in > 0)
			close(cmd->int_in);
		cmd->int_in = open(current->name, O_RDONLY);
	}
	return (0);
}

static int	op_out(t_cmd *cmd, t_std *c)
{
	int	fd;

	if (!access(c->name, F_OK) && access(c->name, W_OK | R_OK))
	{
		cmd->pb = error_permission(c->name, NULL, c->name, cmd);
		return (-1);
	}
	if (!verif_last(cmd, c))
	{
		if (!c->append)
			fd = open(c->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			fd = open(c->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
		close(fd);
	}
	else
	{
		if (!c->append)
			cmd->int_out = open(c->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else
			cmd->int_out = open(c->name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	}
	return (0);
}

void	open_file(t_cmd *cmd, int nb)
{
	t_std	*current;

	current = (*cmd->std);
	cmd->op_nb = nb;
	while (current)
	{
		if (current->in && current->number == cmd->op_nb
			&& op_in(cmd, current) != -1)
			cmd->change_in = 1;
		else if (!current->in && current->number == cmd->op_nb
			&& op_out(cmd, current) != -1)
			cmd->change_out = 1;
		if (cmd->pb != -1)
		{
			delete_hd_file(cmd);
			break ;
		}
		current = current->next;
	}
}
