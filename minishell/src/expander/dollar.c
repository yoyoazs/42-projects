/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:38:33 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 09:26:06 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dollar	*set_info(t_memory_table *mem, char *var, int len)
{
	t_dollar	*info;

	info = gc_malloc(mem, sizeof(t_dollar));
	info->var = gc_strdup(mem, var);
	info->len = len;
	return (info);
}

static void	set_cmd(t_memory_table *mem, char **cmd, size_t *i, t_dollar *info)
{
	char	*tmp;

	tmp = NULL;
	if (info->len <= 0)
	{
		info->len = 1;
		(*i) += info->len + 1;
	}
	if (info->len == 0)
		info->len = -1;
	if ((int)(*i) - info->len - 1 < 0)
		tmp = gc_strdup(mem, "");
	else
		tmp = gc_strndup(mem, (*cmd), (*i) - info->len - 1);
	add_quote(mem, &info->var);
	info->var = gc_strjoin(mem, tmp, info->var);
	if (*i <= ft_strlen(*cmd) && (*cmd)[(*i)])
		info->var = gc_strjoin(mem, info->var, (*cmd) + (*i));
	(*cmd) = info->var;
	gc_free(mem, info);
}

static void	handle_dollar_cmd(t_memory_table *mem, long int cmd, char **var)
{
	char	*tmp;

	tmp = ft_itoa(cmd);
	*var = gc_strdup(mem, tmp);
	free(tmp);
}

char	*get_env_var_quote(t_memory_table *mem, char **env, char *name)
{
	int				i;
	char			*var;
	const size_t	name_len = ft_strlen(name);

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			var = ft_strchr(env[i], '=');
			if (var)
				return (gc_strdup(mem, var + 1));
		}
		i++;
	}
	return (NULL);
}

void	handle_dollar(t_mem_and_cmd *info, char **env, char **cmd, size_t *i)
{
	int		len;
	char	*var;
	char	*tmp;

	len = 0;
	var = NULL;
	tmp = NULL;
	if ((*cmd)[(*i) + 1] == '?')
		handle_dollar_cmd(info->mem, info->cmd, &var);
	else if ((*cmd)[(*i) + 1] == '0')
		var = gc_strdup(info->mem, "minishell");
	else if (!ft_isalnum((*cmd)[(*i) + 1]))
		return ;
	else
	{
		while (ft_isalnum((*cmd)[++(*i)]))
			len++;
		tmp = gc_strndup(info->mem, (*cmd) + (*i) - len, len);
		var = get_env_var_quote(info->mem, env, tmp);
	}
	if (!var)
		var = gc_strdup(info->mem, "");
	gc_free(info->mem, tmp);
	set_cmd(info->mem, cmd, i, set_info(info->mem, var, len));
}
