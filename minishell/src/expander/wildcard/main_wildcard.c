/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:30:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 11:32:35 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dir_path(t_memory_table *mem, char **cmd, size_t *i)
{
	char	*wildcard;
	size_t	len;
	size_t	j;

	len = *i;
	j = 0;
	while (len > 0 && (*cmd)[--len] && (*cmd)[len] != ' ')
		;
	if ((*cmd)[len] == ' ')
		len++;
	while (len + j < ft_strlen(*cmd) && (*cmd)[len + j]
		&& (*cmd)[len + j] != ' ')
		j++;
	wildcard = gc_strndup(mem, *cmd + len, j);
	*i = len + j;
	return (wildcard);
}

void	handle_wildcard(t_memory_table *mem, t_memory_table *mem_ps,
char **cmd, size_t *i)
{
	char	*prefix;
	char	*dir_path;
	t_file	*files;
	char	*str;
	char	*tmp;

	files = NULL;
	str = NULL;
	prefix = get_prefix(mem_ps, cmd, *i);
	dir_path = get_dir_path(mem_ps, cmd, i);
	get_files_multifolder(mem_ps, &files, dir_path, prefix);
	check_file(mem_ps, &files, dir_path);
	str = get_files_string(mem_ps, files);
	if (str)
	{
		tmp = gc_strndup(mem, *cmd, (*i) - ft_strlen(dir_path));
		tmp = gc_strjoin(mem, tmp, str);
		tmp = gc_strjoin(mem, tmp, (*cmd) + *i);
		gc_free(mem, *cmd);
		*cmd = tmp;
		*i += ft_strlen(str);
		gc_free(mem_ps, str);
	}
	gc_free(mem_ps, dir_path);
}
