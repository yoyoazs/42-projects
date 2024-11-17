/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 22:30:56 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:28:12 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_without_esc(const char *str)
{
	size_t	len;
	size_t	i;
	size_t	esc;

	i = -1;
	len = 0;
	esc = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\001')
			esc = 1;
		else if (str[i] == '\002')
			esc = 0;
		else if (esc == 0)
			len++;
	}
	return (len);
}

void	reset_screen(t_readline *readline)
{
	const int	width = get_terminal_width();

	if (isatty(STDOUT_FILENO))
	{
		write(1, "\033[2J\033[1;1H", 10);
		readline->start->x = 1;
		readline->start->y = 1;
		readline->cursor->x = readline->len_prompt
			+ get_string_len_in_terminal(readline->input,
				readline->index, width);
		readline->cursor->y = readline->cursor->x / width;
		readline->cursor->x %= width;
		write(STDOUT_FILENO, readline->prompt, ft_strlen(readline->prompt));
		write(STDOUT_FILENO, readline->input, ft_strlen(readline->input));
		write(STDOUT_FILENO, "  ", 2);
		write(STDOUT_FILENO, "\033[", 2);
		ft_putnbr_fd(readline->cursor->y + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, ";", 1);
		ft_putnbr_fd(readline->cursor->x + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, "H", 1);
	}
}

int	get_terminal_width(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int	get_terminal_height(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_row);
}
