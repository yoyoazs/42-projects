/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:57:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 09:17:42 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_file	*init_file(t_memory_table *mem, char *file,
unsigned int type)
{
	t_file	*new_file;

	new_file = (t_file *)gc_malloc(mem, sizeof(t_file));
	new_file->name = gc_strdup(mem, file);
	new_file->type = type;
	new_file->next = NULL;
	return (new_file);
}

void	*add_file(t_memory_table *mem, t_file **files, char *file,
unsigned int type)
{
	t_file	*new_file;
	t_file	*current;
	t_file	*prev;

	new_file = init_file(mem, file, type);
	if (*files == NULL)
	{
		*files = new_file;
		return (NULL);
	}
	current = *files;
	prev = NULL;
	while (current && ft_strcasecmp(current->name, file) < 0)
	{
		prev = current;
		current = current->next;
	}
	new_file->next = current;
	if (prev)
		prev->next = new_file;
	else
		*files = new_file;
	return (NULL);
}

char	*get_prefix(t_memory_table *mem, char **cmd, size_t len)
{
	char	*wildcard;
	size_t	j;
	size_t	last_slash;

	j = -1;
	last_slash = 0;
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
		wildcard = gc_strdup(mem, "./");
	return (wildcard);
}

static int	get_lenght(t_file *files)
{
	t_file	*tmp;
	int		total_length;

	total_length = 0;
	tmp = files;
	while (tmp)
	{
		total_length += ft_strlen(tmp->name) + 1;
		tmp = tmp->next;
	}
	return (total_length);
}

char	*get_files_string(t_memory_table *mem, t_file *files)
{
	t_file	*tmp;
	char	*files_string;
	char	*ptr;
	size_t	total_length;

	total_length = get_lenght(files);
	if (total_length == 0)
		return (NULL);
	files_string = (char *)gc_malloc(mem, sizeof(char) * total_length + 1);
	ptr = files_string;
	tmp = files;
	while (tmp)
	{
		ft_strcpy(ptr, tmp->name);
		ptr += ft_strlen(tmp->name);
		*ptr++ = ' ';
		tmp = tmp->next;
	}
	*(ptr - 1) = '\0';
	return (files_string);
}
