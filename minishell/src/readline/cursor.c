/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:31:20 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 09:33:55 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_cursor_pos(t_cursor *c)
{
	char	buf[32];
	char	*tmp;
	int		i;

	c->x = 0;
	c->y = 0;
	write(1, "\033[6n", 4);
	i = 0;
	while (read(0, buf + i, 1) > 0)
	{
		if (buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
	tmp = ft_strchr(buf, '[');
	c->y = ft_atoi(tmp + 1);
	c->x = ft_atoi(ft_strchr(tmp, ';') + 1);
}

void	goto_end_line(t_readline *rl)
{
	int	i;

	i = ft_strlen(rl->input);
	rl->index = i;
	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, i, rl->last_dim->x);
	rl->cursor->y = rl->start->y + rl->cursor->x / rl->last_dim->x;
	rl->cursor->x %= rl->last_dim->x;
	if (rl->cursor->x > 0 && rl->cursor->y >= rl->last_dim->y)
		rl->cursor->y++;
	if (rl->start->y - rl->cursor->y < 1)
		rl->start->y = rl->cursor->y;
	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->cursor->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->cursor->x + 1, STDOUT_FILENO);
	write(STDOUT_FILENO, "H", 1);
}

static void	cursor_gestion_ctrl(int direction, t_readline *rl)
{
	if (direction == CTRL_RIGHT)
	{
		while (rl->input[rl->index] && rl->input[rl->index] == ' ')
			rl->index++;
		while (rl->input[rl->index] && rl->input[rl->index] != ' ')
			rl->index++;
	}
	if (direction == CTRL_LEFT)
	{
		while (rl->index > 0 && rl->input[rl->index - 1] == ' ')
			rl->index--;
		while (rl->index > 0 && rl->input[rl->index - 1] != ' ')
			rl->index--;
	}
}

void	set_cursor_pos(t_readline *rl, int width)
{
	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, rl->index, width);
	rl->cursor->y = rl->start->y + rl->cursor->x / width;
	rl->cursor->x %= width;
	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->cursor->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->cursor->x + 1, STDOUT_FILENO);
	write(STDOUT_FILENO, "H", 1);
}

void	cursor_gestion(int direction, t_readline *rl)
{
	const int	width = get_terminal_width();

	if (direction == RIGHT_KEY)
	{
		if (rl->input[rl->index] == '\0')
			return ;
		while (rl->input[rl->index] && (rl->input[rl->index + 1] & 0xC0) == 128)
			rl->index++;
		rl->index++;
	}
	if (direction == LEFT_KEY)
	{
		if (rl->index <= 0)
			return ;
		while ((rl->index > 0) && (rl->input[rl->index - 1] & 0xC0) == 0x80)
			rl->index--;
		rl->index--;
	}
	cursor_gestion_ctrl(direction, rl);
	if (direction == HOME)
		rl->index = 0;
	if (direction == END)
		rl->index = ft_strlen(rl->input);
	set_cursor_pos(rl, width);
}
