/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:30:26 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 21:24:08 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	history_up(t_readline *rl)
{
	if (rl->history->prev == NULL)
		return (0);
	if (rl->history->next == NULL)
	{
		gc_free(rl->mem, rl->history->line);
		rl->history->line = gc_strdup(rl->mem, rl->input);
	}
	if (rl->history->prev)
		rl->history = rl->history->prev;
	return (1);
}

static void	history_set_cursor(t_readline *rl)
{
	const int	width = get_terminal_width();

	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, rl->index, width) + 1;
	rl->cursor->y = rl->start->y + rl->cursor->x / width;
	if (rl->cursor->y > rl->last_dim->y)
	{
		rl->start->y -= rl->cursor->y - rl->last_dim->y;
		rl->cursor->y = rl->last_dim->y;
	}
	rl->cursor->x %= width;
}

void	history(t_readline *rl, int direction)
{
	if (rl->history == NULL)
		return ;
	if (direction == UP_KEY && !history_up(rl))
		return ;
	else if (direction == DOWN_KEY)
	{
		if (rl->history->next == NULL)
			return ;
		rl->history = rl->history->next;
	}
	gc_free(rl->mem, rl->input);
	rl->index = ft_strlen(rl->history->line);
	rl->max_len_input = (rl->index / 16 + 1) * 16;
	rl->input = gc_malloc(rl->mem, rl->max_len_input);
	ft_strcpy(rl->input, rl->history->line);
	write(STDOUT_FILENO, "\033[", 3);
	ft_putnbr_fd(rl->start->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->start->x, STDOUT_FILENO);
	write(STDOUT_FILENO, "H\033[J", 4);
	write(STDOUT_FILENO, rl->prompt, ft_strlen(rl->prompt));
	write(STDOUT_FILENO, rl->input, rl->index);
	history_set_cursor(rl);
}

void	get_historic(t_readline *rl)
{
	int		fd;
	char	*line;

	fd = open(".msh_history", O_CREAT | O_RDWR, 0666);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		add_to_history(rl, line, false);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	save_historic(void)
{
	int			fd;
	t_history	*current;
	t_readline	*rl;

	rl = readline(NULL, NULL, NULL, true);
	fd = open(".msh_history", O_CREAT | O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		return ;
	current = rl->history;
	while (current->prev)
		current = current->prev;
	while (current)
	{
		if (current->to_save && ft_strlen(current->line) > 0)
		{
			write(fd, current->line, ft_strlen(current->line));
			write(fd, "\n", 1);
		}
		current = current->next;
	}
	close(fd);
}
