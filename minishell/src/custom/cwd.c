/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:15:59 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/07 10:56:37 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_get_cwd(t_data_ms *data, char **cwd)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = get_env_var(data->mem, data->env, "PWD");
	if (tmp == NULL)
	{
		tmp = getcwd(NULL, 0);
		i = 1;
	}
	*cwd = gc_strdup(data->mem, tmp);
	if (!i)
		gc_free(data->mem, tmp);
	else
		free(tmp);
}

char	*get_cwd(t_data_ms *data, int basename)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	init_get_cwd(data, &cwd);
	home = get_env_var(data->mem, data->env, "HOME");
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = gc_strjoin(data->mem, gc_strdup(data->mem, "~"),
				cwd + ft_strlen(home));
		gc_free(data->mem, cwd);
		cwd = tmp;
	}
	if (basename)
	{
		tmp = ft_strrchr(cwd, '/');
		if (tmp)
		{
			tmp = gc_strdup(data->mem, tmp + 1);
			gc_free(data->mem, cwd);
			cwd = tmp;
		}
	}
	gc_free(data->mem, home);
	return (cwd);
}
