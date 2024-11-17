/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:30:00 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 13:36:09 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_ctrl(t_readline *rl)
{
	int	next3;

	next3 = read_key();
	if (next3 == 59)
	{
		next3 = read_key();
		if (next3 == 53)
		{
			next3 = read_key();
			if (next3 == 67)
				cursor_gestion(CTRL_RIGHT, rl);
			if (next3 == 68)
				cursor_gestion(CTRL_LEFT, rl);
		}
	}
}

static void	handle_next_keys(t_readline *rl)
{
	int	next1;
	int	next2;
	int	next3;

	next1 = read_key();
	if (next1 != 91)
		return ;
	next2 = read_key();
	if (next2 == 51)
	{
		next3 = read_key();
		if (next3 == 126)
			delete_char_forward(rl);
	}
	if (next2 == HOME || next2 == END)
		cursor_gestion(next2, rl);
	if (next2 == 49)
		handle_ctrl(rl);
	if (next2 == UP_KEY)
		history(rl, UP_KEY);
	if (next2 == DOWN_KEY)
		history(rl, DOWN_KEY);
	if ((next2 == RIGHT_KEY || next2 == LEFT_KEY))
		cursor_gestion(next2, rl);
}

static void	check_new_line(t_readline *rl)
{
	while (rl->input[rl->index] != '\0')
		rl->index++;
	if (rl->index == 0)
	{
		rl->input[0] = ' ';
		rl->input[1] = '\0';
	}
	rl->listen = false;
}

void	check_input(t_readline	*rl)
{
	int	c;

	while (rl->listen)
	{
		c = read_key();
		if (c == 4 && ft_strlen(rl->input) == 0)
			break ;
		else if (c == 10)
			check_new_line(rl);
		else if (c == '\t')
			auto_completion(rl);
		else if (c == 12)
			reset_screen(rl);
		else if (c == 27)
			handle_next_keys(rl);
		else if (c == 127)
			delete_char(rl);
		else if (c == -1 || c == 4 || (c >= 0 && c <= 31) || c == 127)
			continue ;
		else
			insert_char(rl, c, get_terminal_width());
	}
}
