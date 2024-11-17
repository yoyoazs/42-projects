/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:38:32 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:29:39 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_height(int rows)
{
	t_readline	*rl;

	rl = (t_readline *)readline(NULL, NULL, NULL, 1);
	rl->start->y = rl->start->y + rows;
	if (rl->start->y > get_terminal_height())
		rl->start->y = get_terminal_height();
}

void	print_in_columns(char **strings, int count, int column_width,
int width)
{
	int			columns;
	int			rows;
	int			i;
	int			j;

	bubble_sort(strings, count);
	columns = width / (column_width + 2);
	if (columns == 0)
		columns = 1;
	rows = (count + columns - 1) / columns;
	i = -1;
	while (++i < rows)
	{
		j = -1;
		while (++j < columns)
		{
			if (j * rows + i < count)
				printf("%-*s  ", column_width, strings[j * rows + i]);
		}
		printf("\n");
	}
}

void	realloc_input_cmd(t_readline *rl, char **cmds)
{
	char	*tmp;

	rl->max_len_input = ((ft_strlen(rl->input)
				+ ft_strlen(cmds[0])) / 16 + 1) * 16;
	tmp = gc_strdup(rl->mem, rl->input);
	gc_free(rl->mem, rl->input);
	rl->input = gc_malloc(rl->mem, rl->max_len_input);
	ft_strcpy(rl->input, tmp);
	gc_free(rl->mem, tmp);
}

void	print_cmd_list(t_readline	*rl, char **cmds, int count)
{
	goto_end_line(rl);
	write(1, "\n", 1);
	print_in_columns(cmds, count, get_max_length(cmds, count),
		get_terminal_width());
}
