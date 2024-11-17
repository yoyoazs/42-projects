/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:15:56 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/08 15:44:02 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(t_memory_table *mem, char **env, char *name)
{
	int				i;
	const size_t	name_len = ft_strlen(name);

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (gc_strdup(mem, ft_strchr(env[i], '=') + 1));
		i++;
	}
	return (NULL);
}

bool	is_empty(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'))
		i++;
	if (str[i])
		return (0);
	return (1);
}

void	handle_non_interactive_mode(void)
{
	write(2, "minishell: error: non-interactive mode\n", 39);
	gc_exit(1);
}
