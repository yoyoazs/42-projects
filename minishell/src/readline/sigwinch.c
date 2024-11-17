/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigwinch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:14:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 13:42:04 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_ligne(t_readline *rl)
{
	const int	width = get_terminal_width();

	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->start->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->start->x, STDOUT_FILENO);
	write(STDOUT_FILENO, "H", 1);
	write(STDOUT_FILENO, "\033[J", 3);
	ft_putstr_fd(rl->prompt, STDOUT_FILENO);
	ft_putstr_fd(rl->input, STDOUT_FILENO);
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

void	handle_sigwinch(int sig)
{
	const int	width = get_terminal_width();
	const int	height = get_terminal_height();
	t_readline	*rl;

	rl = (t_readline *)readline(NULL, NULL, NULL, 1);
	if ((!rl->listen && sig != SIGWINCH)
		|| (width == rl->last_dim->x && height == rl->last_dim->y))
		return ;
	if (rl->start->x > width)
	{
		rl->start->x = 0;
		rl->start->y++;
	}
	reset_ligne(rl);
	rl->last_dim->x = width;
	rl->last_dim->y = height;
}
