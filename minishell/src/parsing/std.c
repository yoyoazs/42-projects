/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:49:23 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 09:35:28 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_std_end(t_data_ms *data, t_subcommand *subcommand, int number)
{
	t_std	*current;
	t_std	*out;

	current = subcommand->std;
	while (current->next && current->next->number != number
		&& current->next->number < number)
		current = current->next;
	out = gc_malloc(data->mem, sizeof(t_std));
	out->next = NULL;
	if (current->next)
		out->next = current->next;
	out->name = gc_strdup(data->mem, "/dev/stdout");
	out->append = false;
	out->in = false;
	out->lim = false;
	out->lim_crafted = false;
	out->number = number;
	current->next = out;
}

void	add_std(t_data_ms *data, t_subcommand *sbcmd, char *name, int *tab)
{
	t_std	*current;
	int		i;

	i = -1;
	current = sbcmd->std;
	while (current->next)
		current = current->next;
	current->next = gc_malloc(data->mem, sizeof(t_std));
	current->next->next = NULL;
	current->next->name = gc_strdup(data->mem, name);
	current->next->append = tab[0];
	current->next->lim_crafted = false;
	current->next->in = tab[1];
	current->next->lim = tab[2];
	current->next->number = tab[3];
	current->next->expand = true;
	while (current->name[++i])
	{
		if (current->name[i] == '\'' || current->name[i] == '"')
		{
			current->expand = false;
			break ;
		}
	}
}

void	set_std(t_data_ms *data, t_subcommand **subcommand)
{
	(*subcommand)->std = gc_malloc(data->mem, sizeof(t_std));
	(*subcommand)->std->next = NULL;
	(*subcommand)->std->name = gc_strdup(data->mem, "/dev/stdin");
	(*subcommand)->std->append = false;
	(*subcommand)->std->in = true;
	(*subcommand)->std->lim = false;
	(*subcommand)->std->lim_crafted = false;
	(*subcommand)->std->number = 0;
}

void	remove_quotes(t_memory_table *mem, char **str)
{
	char	*tmp;
	char	quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	quote = 0;
	tmp = gc_malloc(mem, ft_strlen(*str) + 1);
	while ((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '"') && !quote)
			quote = (*str)[i];
		else if ((*str)[i] == quote)
			quote = 0;
		else
			tmp[j++] = (*str)[i];
		i++;
	}
	tmp[j] = '\0';
	gc_free(mem, *str);
	*str = tmp;
}

char	*std_get_file(t_data_ms *data)
{
	t_std	*current;
	char	*tmp;
	char	*tmp_name;

	tmp = NULL;
	current = data->std;
	while (current && tmp == NULL)
	{
		if (current->name && !current->lim)
		{
			tmp_name = gc_strdup(data->mem, current->name);
			if (!get_file(data, &current->name))
				tmp = tmp_name;
			if (!tmp)
				gc_free(data->mem, tmp_name);
		}
		if (current->name && !tmp)
			remove_quotes(data->mem, &current->name);
		current = current->next;
	}
	if (tmp)
		data->cmd = 1;
	return (tmp);
}
