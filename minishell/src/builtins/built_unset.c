/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:51:46 by npigeon           #+#    #+#             */
/*   Updated: 2024/08/02 17:30:58 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	remove_env(t_memory_table *mem, int i, char ***env)
{
	if (!(*env))
		return ;
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	gc_free(mem, (*env)[i]);
	return ;
}

ssize_t	find_env(char *to_find, char ***env)
{
	int	i;

	i = 0;
	if (!(*env) || !to_find)
		return (-1);
	while ((*env)[i])
	{
		if (!ft_strncmp(to_find, (*env)[i], ft_strlen(to_find)) &&
			((*env)[i][ft_strlen(to_find)] == '=' ||
			(*env)[i][ft_strlen(to_find)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

int	run_unset(char **args, char ***env, t_cmd *cmd)
{
	size_t	i;
	ssize_t	index;

	if (!args[1])
		return (0);
	i = 0;
	while (args[++i])
	{
		index = find_env(args[i], env);
		if (index != -1)
		{
			if ((*env)[index])
				remove_env(cmd->mem, index, env);
		}
	}
	return (0);
}
