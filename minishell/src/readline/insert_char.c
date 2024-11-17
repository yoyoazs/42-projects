/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:37:06 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 09:08:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_display(t_readline *rl, unsigned char *bytes, int len)
{
	write(STDOUT_FILENO, bytes, len);
	write(STDOUT_FILENO, rl->input + rl->index,
		ft_strlen(rl->input + rl->index));
	write(STDOUT_FILENO, " ", 1);
	write(STDOUT_FILENO, "\033[", 2);
	ft_putnbr_fd(rl->cursor->y, STDOUT_FILENO);
	write(STDOUT_FILENO, ";", 1);
	ft_putnbr_fd(rl->cursor->x + 1, STDOUT_FILENO);
	write(STDOUT_FILENO, "H", 1);
}

static void	realloc_input(t_readline *rl)
{
	char	*tmp;

	rl->max_len_input *= 2;
	tmp = (char *)gc_malloc(rl->mem, rl->max_len_input * sizeof(char));
	ft_strcpy(tmp, rl->input);
	gc_free(rl->mem, rl->input);
	rl->input = tmp;
}

static int	insert_char_2(t_readline *rl, int width, int last_nline)
{
	int	new_nline;

	new_nline = (rl->len_prompt + get_string_len_in_terminal(rl->input,
				ft_strlen(rl->input), width)) / width;
	if (new_nline > last_nline && rl->start->y
		+ new_nline > get_terminal_height())
	{
		write(STDOUT_FILENO, "\033[", 2);
		ft_putnbr_fd(rl->start->y, STDOUT_FILENO);
		write(STDOUT_FILENO, ";", 1);
		ft_putnbr_fd(rl->start->x, STDOUT_FILENO);
		write(STDOUT_FILENO, "H\033[J", 4);
		ft_putstr_fd(rl->prompt, STDOUT_FILENO);
		ft_putstr_fd(rl->input, STDOUT_FILENO);
		write(STDOUT_FILENO, " \033[", 3);
		ft_putnbr_fd(rl->cursor->y - 1, STDOUT_FILENO);
		write(STDOUT_FILENO, ";", 1);
		ft_putnbr_fd(rl->cursor->x, STDOUT_FILENO);
		write(STDOUT_FILENO, "H", 1);
		rl->start->y--;
		return (1);
	}
	return (0);
}

void	insert_char(t_readline *rl, int unicode, int width)
{
	int				len;
	unsigned char	bytes[5];
	int				last_nline;

	last_nline = (rl->len_prompt + get_string_len_in_terminal(rl->input,
				ft_strlen(rl->input), width)) / width;
	ft_memset(bytes, 0, 5);
	len = get_bytes(unicode, bytes);
	if (ft_strlen(rl->input) + len >= rl->max_len_input)
		realloc_input(rl);
	ft_memmove(rl->input + rl->index + len, rl->input + rl->index,
		ft_strlen(rl->input + rl->index) + 1);
	ft_memmove(rl->input + rl->index, bytes, len);
	rl->index += len;
	rl->cursor->x = rl->start->x - 1 + rl->len_prompt
		+ get_string_len_in_terminal(rl->input, rl->index, width);
	rl->cursor->y = rl->start->y + rl->cursor->x / width;
	rl->cursor->x %= width;
	if (insert_char_2(rl, width, last_nline))
		return ;
	update_display(rl, bytes, len);
}
