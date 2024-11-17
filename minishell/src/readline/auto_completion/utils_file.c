/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:14:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:27:25 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files(t_readline *rl, int count, char **files, char *tmp)
{
	int	i;

	i = 0;
	if (tmp != NULL)
		gc_free(rl->mem, tmp);
	while (++i < count)
		gc_free(rl->mem, files[i]);
}

char	*get_prefix_file(t_memory_table *mem, char **cmd, size_t len)
{
	char	*wildcard;
	size_t	j;
	size_t	last_slash;

	j = -1;
	last_slash = 0;
	if (!*cmd || len > ft_strlen(*cmd))
		return (gc_strdup(mem, ""));
	while (len > 0 && (*cmd)[--len] && (*cmd)[len] != ' ')
		;
	if ((*cmd)[len] == ' ')
		len++;
	while (len + ++j < ft_strlen(*cmd) && (*cmd)[len + j]
		&& (*cmd)[len + j] != ' ' && (*cmd)[len + j] != '*'
		&& (*cmd)[len + j] != '?' && (*cmd)[len + j] != '[')
		if ((*cmd)[len + j] == '/')
			last_slash = j;
	if (last_slash)
		wildcard = gc_strndup(mem, *cmd + len, last_slash + 1);
	else if ((*cmd)[len] == '/')
		wildcard = gc_strdup(mem, "/");
	else
		wildcard = gc_strdup(mem, "");
	return (wildcard);
}
