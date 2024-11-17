/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:28:49 by npigeon           #+#    #+#             */
/*   Updated: 2024/07/24 23:04:48 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths_rightpaths(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (cmd->paths)
	{
		while ((cmd->paths)[++i])
			gc_free(cmd->mem, (cmd->paths)[i]);
	}
	gc_free(cmd->mem, cmd->paths);
	gc_free(cmd->mem, cmd->right_path);
}

void	free_paths_rightpaths_cut(t_cmd *cmd)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	free_paths_rightpaths(cmd);
	while ((cmd->cut)[i])
	{
		while ((cmd->cut)[i][++j])
			gc_free(cmd->mem, (cmd->cut)[i][j]);
		gc_free(cmd->mem, (cmd->cut)[i]);
		i++;
		j = -1;
	}
	gc_free(cmd->mem, cmd->cut);
}
