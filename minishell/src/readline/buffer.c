/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:27:02 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/12 01:09:51 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_unbuffered_input(t_readline *readline)
{
	struct termios	newt;

	if (tcgetattr(STDIN_FILENO, &newt))
		return (0);
	if (tcgetattr(STDIN_FILENO, &readline->orig_term))
		return (0);
	newt = readline->orig_term;
	newt.c_iflag = 0x4500;
	newt.c_oflag = 0x0005;
	newt.c_cflag = 0x00bf;
	newt.c_lflag = 0x8a31;
	newt.c_cc[VMIN] = 1;
	newt.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newt) == -1)
		return (0);
	return (1);
}

void	restore_input_buffering(t_readline *readline)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &readline->orig_term);
}
