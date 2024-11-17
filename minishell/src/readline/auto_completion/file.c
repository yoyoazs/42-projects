/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:09:27 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:39:18 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_files_tab(t_memory_table *mem, t_file *files)
{
	t_file	*tmp;
	t_file	*tmp2;
	char	**tab;
	int		i;

	i = 0;
	tmp = files;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	tab = gc_malloc(mem, sizeof(char *) * (i + 1));
	i = 0;
	tmp = files;
	while (tmp)
	{
		tab[i] = tmp->name;
		i++;
		tmp2 = tmp->next;
		gc_free(mem, tmp);
		tmp = tmp2;
	}
	tab[i] = NULL;
	return (tab);
}

static void	check_file_and_remove_prefix(t_memory_table	*mem,
t_file **files, char *path, char *prefix)
{
	t_file	*tmp;
	char	*file;

	tmp = *files;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "./", 2) == 0
			&& ft_strncmp(path, "./", 2) != 0)
		{
			file = gc_strdup(mem, tmp->name + 2);
			gc_free(mem, tmp->name);
			tmp->name = file;
		}
		if (tmp->type == DT_DIR && tmp->name[ft_strlen(tmp->name) - 1] != '/')
			tmp->name = gc_strjoin(mem, tmp->name, "/");
		if (ft_strncmp(tmp->name, prefix, ft_strlen(prefix)) == 0)
		{
			file = gc_strdup(mem, tmp->name + ft_strlen(prefix));
			gc_free(mem, tmp->name);
			tmp->name = file;
		}
		tmp = tmp->next;
	}
}

static char	**get_autocompletion_file(t_memory_table *mem, char **cmd,
size_t *i)
{
	char	*prefix;
	char	*dir_path;
	t_file	*files;
	char	**str;

	files = NULL;
	str = NULL;
	*cmd = gc_strjoin(mem, *cmd, "*");
	prefix = get_prefix(mem, cmd, *i);
	dir_path = get_dir_path(mem, cmd, i);
	get_files_multifolder(mem, &files, dir_path, prefix);
	check_file_and_remove_prefix(mem, &files, dir_path, prefix);
	str = get_files_tab(mem, files);
	if (str)
		return (str);
	gc_free(mem, prefix);
	return (NULL);
}

static void	set_cmd_file(t_readline *rl, size_t i, char **cmd, char **files)
{
	int		len;
	char	*tmp;
	char	*prefix;
	size_t	new_len;

	len = 0;
	while (rl->input[i + len] && rl->input[i + len] != ' ')
		len++;
	prefix = get_prefix_file(rl->mem, cmd, i);
	new_len = ft_strlen(rl->input) - len + ft_strlen(prefix)
		+ ft_strlen(files[0]) + 1;
	if (new_len > rl->max_len_input)
		realloc_input_cmd(rl, files);
	tmp = gc_malloc(rl->mem, rl->max_len_input);
	ft_strlcpy(tmp, rl->input, i + 1);
	ft_strlcat(tmp, prefix, new_len);
	ft_strlcat(tmp, files[0], new_len);
	if (rl->input[i + len])
		ft_strlcat(tmp, rl->input + i + len, new_len);
	gc_free(rl->mem, rl->input);
	rl->input = tmp;
	rl->index = i + ft_strlen(files[0]) + ft_strlen(prefix);
	gc_free(rl->mem, prefix);
}

void	complete_file(t_readline *rl, size_t i)
{
	char	**files;
	char	*tmp;
	int		count;
	size_t	len;

	len = 0;
	while (rl->input[i + len] && rl->input[i + len] != ' ')
		len++;
	if (len == 0)
		return ;
	tmp = gc_strndup(rl->mem, rl->input + i, len);
	files = get_autocompletion_file(rl->mem, &tmp, &len);
	count = 0;
	while (files && files[count])
		count++;
	if (count > 1)
	{
		goto_end_line(rl);
		write(1, "\n", 1);
		print_in_columns(files, count, get_max_length(files, count),
			get_terminal_width());
	}
	else if (count == 1)
		set_cmd_file(rl, i, &tmp, files);
	free_files(rl, count, files, tmp);
}
