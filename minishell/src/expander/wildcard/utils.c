/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:54:30 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/09 09:08:44 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	while (*s1 && (ft_tolower((unsigned char)*s1)
			== ft_tolower((unsigned char)*s2)))
	{
		s1++;
		s2++;
	}
	return (ft_tolower((unsigned char)*s1)
		- ft_tolower((unsigned char)*s2));
}

void	add_folder(t_memory_table *mem, t_folder **folders, char *name, int i)
{
	t_folder	*new_folder;
	t_folder	*current;
	t_folder	*prev;

	new_folder = (t_folder *)gc_malloc(mem, sizeof(t_folder));
	new_folder->name = gc_strdup(mem, name);
	new_folder->nb_folders = i;
	new_folder->next = NULL;
	current = *folders;
	prev = NULL;
	if (*folders == NULL)
	{
		*folders = new_folder;
		return ;
	}
	while (current)
	{
		prev = current;
		current = current->next;
	}
	prev->next = new_folder;
}

static void	remove_not_dir(t_memory_table *mem, t_file **prev, t_file **tmp,
t_file ***files)
{
	if ((*prev))
		(*prev)->next = (*tmp)->next;
	else
		**files = (*tmp)->next;
	gc_free(mem, (*tmp)->name);
	gc_free(mem, (*tmp));
	if ((*prev))
		(*tmp) = (*prev)->next;
	else
		(*tmp) = **files;
}

void	check_file(t_memory_table *mem, t_file **files, char *pa)
{
	t_file	*tmp;
	t_file	*prev;
	char	*file;

	tmp = *files;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "./", 2) == 0 && ft_strncmp(pa, "./", 2) != 0)
		{
			file = gc_strdup(mem, tmp->name + 2);
			gc_free(mem, tmp->name);
			tmp->name = file;
		}
		if (tmp->type == DT_DIR && tmp->name[ft_strlen(tmp->name) - 1] != '/'
			&& pa[ft_strlen(pa) - 1] == '/')
			tmp->name = gc_strjoin(mem, tmp->name, "/");
		if (pa[ft_strlen(pa) - 1] == '/' && tmp->type != DT_DIR)
		{
			remove_not_dir(mem, &prev, &tmp, &files);
			continue ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

t_info_ff	*set_ff(t_memory_table *mem, int nb, t_folder **folder,
t_file **files)
{
	t_info_ff	*info;

	info = gc_malloc(mem, sizeof(t_info_ff));
	info->nb = nb;
	info->folder = folder;
	info->files = files;
	return (info);
}
