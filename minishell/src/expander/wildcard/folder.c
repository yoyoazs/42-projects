/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:55:56 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/09 09:10:09 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_all_files_loop(t_memory_table *mem, t_folder *current,
t_info_ff *info, struct dirent *entry)
{
	char	*new_path;

	if (((ft_fnmatch(mem, info->name, entry->d_name) && info->name[0] == '.'
				&& entry->d_name[0] == '.')
			|| (ft_fnmatch(mem, info->name, entry->d_name)
				&& info->name[0] != '.' && entry->d_name[0] != '.')
			|| (ft_strlen(entry->d_name) == 1 && info->name[0] == '.'
				&& entry->d_name[0] == '.')))
	{
		new_path = gc_strdup(mem, current->name);
		if (current->name[ft_strlen(current->name) - 1] != '/')
			new_path = gc_strjoin(mem, new_path, "/");
		new_path = gc_strjoin(mem, new_path, entry->d_name);
		add_file(mem, info->files, new_path, entry->d_type);
		gc_free(mem, new_path);
	}
}

static void	get_all_files(t_memory_table *mem, char *name, t_info_ff *info)
{
	t_folder		*current;
	DIR				*dir;
	struct dirent	*entry;

	info->name = name;
	current = (*info->folder);
	while (current)
	{
		if (current->nb_folders == info->nb - 1)
		{
			dir = opendir(current->name);
			if (dir)
			{
				entry = readdir(dir);
				while (entry != NULL)
				{
					get_all_files_loop(mem, current, info, entry);
					entry = readdir(dir);
				}
				closedir(dir);
			}
		}
		current = current->next;
	}
	gc_free(mem, info);
}

static void	get_folders_loop(t_memory_table *mem, t_info_ff *info,
struct dirent *entry, t_folder *s_folders)
{
	char	*new_path;

	if (((ft_fnmatch(mem, info->name, entry->d_name) && info->name[0] == '.'
				&& entry->d_name[0] == '.')
			|| (ft_fnmatch(mem, info->name, entry->d_name)
				&& info->name[0] != '.' && entry->d_name[0] != '.')
			|| (ft_strlen(entry->d_name) == 1 && info->name[0] == '.'
				&& entry->d_name[0] == '.'))
		&& (entry->d_type == DT_DIR || entry->d_type == DT_LNK))
	{
		new_path = gc_strdup(mem, s_folders->name);
		if (s_folders->name[ft_strlen(s_folders->name) - 1] != '/')
			new_path = gc_strjoin(mem, new_path, "/");
		new_path = gc_strjoin(mem, new_path, entry->d_name);
		add_folder(mem, info->folder, new_path, info->nb);
		gc_free(mem, new_path);
	}
}

static void	get_folders(t_memory_table *mem, t_folder **folders, int i,
char *name)
{
	t_folder		*s_folders;
	DIR				*dir;
	struct dirent	*entry;
	t_info_ff		*info;

	s_folders = *folders;
	while (s_folders)
	{
		if (s_folders->nb_folders == i - 1)
		{
			dir = opendir(s_folders->name);
			entry = readdir(dir);
			while (entry != NULL)
			{
				info = set_ff(mem, i, folders, (t_file **) NULL);
				info->name = name;
				get_folders_loop(mem, info, entry, s_folders);
				gc_free(mem, info);
				entry = readdir(dir);
			}
			closedir(dir);
		}
		s_folders = s_folders->next;
	}
}

void	get_files_multifolder(t_memory_table *mem, t_file **files,
char *dir_path, char *prefix)
{
	t_folder	*folders;
	char		**folders_path;
	int			i;
	int			numbers;

	folders = NULL;
	folders_path = NULL;
	if (ft_strncmp(prefix, "./", 2) == 0 && ft_strncmp(dir_path, "./", 2) != 0)
		folders_path = gc_split(mem, dir_path + ft_strlen(prefix) - 2, '/');
	else
		folders_path = gc_split(mem, dir_path + ft_strlen(prefix), '/');
	numbers = 1;
	add_folder(mem, &folders, prefix, 0);
	i = -1;
	while (folders_path[++i] && folders_path[i + 1])
	{
		get_folders(mem, &folders, numbers, folders_path[i]);
		numbers++;
	}
	if (i == 0 && !folders_path[0])
		get_all_files(mem, dir_path, set_ff(mem, numbers, &folders, files));
	else
		get_all_files(mem, folders_path[i],
			set_ff(mem, numbers, &folders, files));
}
