/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:48:51 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 10:33:57 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_char_width(const char *str, size_t *len)
{
	const unsigned char	c = (unsigned char)str[0];

	if (c < 0x80)
	{
		*len = 1;
		return (1);
	}
	else if ((c & 0xE0) == 0xC0)
	{
		*len = 2;
		return (1);
	}
	else if ((c & 0xF0) == 0xE0)
	{
		*len = 3;
		return (1);
	}
	else if ((c & 0xF8) == 0xF0)
	{
		*len = 4;
		return (2);
	}
	*len = 1;
	return (1);
}

size_t	get_string_len_in_terminal(const char *str, size_t max,
size_t terminal_width)
{
	size_t	current_line_width;
	size_t	total_height;
	size_t	char_len;
	size_t	i;
	int		char_width;

	current_line_width = 0;
	total_height = 1;
	i = 0;
	while (str[i] != '\0' && i < max)
	{
		char_width = get_char_width(&str[i], &char_len);
		if (current_line_width + char_width > terminal_width)
		{
			total_height++;
			current_line_width = char_width;
		}
		else
			current_line_width += char_width;
		i += char_len;
	}
	return ((total_height - 1) * terminal_width + current_line_width);
}

void	delete_char_forward(t_readline *rl)
{
	size_t		len_utf8;
	const int	width = get_terminal_width();

	len_utf8 = 0;
	if (rl->input[rl->index] == '\0')
		return ;
	while (rl->input[rl->index + len_utf8]
		&& (rl->input[rl->index + len_utf8 + 1] & 0xC0) == 0x80)
		len_utf8++;
	if (rl->input[rl->index + len_utf8])
		len_utf8++;
	ft_memmove(rl->input + rl->index, rl->input + rl->index + len_utf8,
		ft_strlen(rl->input) - rl->index - len_utf8 + 1);
	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, rl->index, width);
	rl->cursor->y = rl->start->y + rl->cursor->x / width;
	rl->cursor->x %= width;
	update_display(rl, (unsigned char *)"", 0);
}

void	delete_char_2(t_readline *rl)
{
	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->start->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->start->x, STDOUT_FILENO);
	write(STDOUT_FILENO, "H\033[J", 4);
	ft_putstr_fd(rl->prompt, STDOUT_FILENO);
	ft_putstr_fd(rl->input, STDOUT_FILENO);
	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->cursor->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->cursor->x, STDOUT_FILENO);
	write(STDOUT_FILENO, "H", 1);
	if (rl->input[rl->index] != '\0')
		write(STDOUT_FILENO, "\033[D", 3);
}

void	delete_char(t_readline *rl)
{
	size_t			start;
	const size_t	width = get_terminal_width();

	if (rl->index <= 0)
		return ;
	start = rl->index - 1;
	while (start > 0 && (rl->input[start] & 0xC0) == 0x80)
		start--;
	ft_memmove(rl->input + start, rl->input + rl->index,
		ft_strlen(rl->input) - rl->index + 1);
	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, rl->index, width) + 1;
	rl->cursor->y = rl->start->y + rl->cursor->x / width;
	rl->cursor->x %= width;
	rl->index = start;
	delete_char_2(rl);
}
