/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 09:47:14 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/06 10:30:37 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

int	var_exist(char **env, char *key)
{
	int	i;

	i = -1;
	if (!ft_strlen(key))
		return (-1);
	while (env[++i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key))
			&& (env[i][ft_strlen(key)] == '\0'
			|| env[i][ft_strlen(key)] == '='))
			return (i);
	}
	return (-1);
}

void	change_var(char ***env, char *key, char *value, t_memory_table *mem)
{
	const int	pos = var_exist(*env, key);
	size_t		value_len;

	value_len = ft_strlen(value);
	if (!value_len)
		return ;
	gc_free(mem, (*env)[pos]);
	(*env)[pos] = gc_strjoin(mem, key, value);
}

int	str_is_alphanum(char *arg, int delim)
{
	int	i;

	i = 0;
	while (i < delim)
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
