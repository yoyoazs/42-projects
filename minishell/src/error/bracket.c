/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:34:28 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/08 15:17:08 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_bracket(t_memory_table *mem, char **line, char *op)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(op, 2);
	ft_putstr_fd("'\n", 2);
	gc_free(mem, *line);
	*line = NULL;
}

void	check_error_bracket(t_memory_table *mem, char **line, size_t i,
int *bracket)
{
	const int	bfor = before_word(line, i);
	int			next;

	if ((*line)[i] == '(')
	{
		if (bfor > 0 && !(((*line)[bfor] == '&' && (*line)[bfor - 1] == '&')
			|| ((*line)[bfor] == '|' && (*line)[bfor - 1] == '|')))
			print_error_bracket(mem, line, "(");
		else
		{
			next = next_word(line, i + 1);
			if ((*line)[next] == '#')
				print_error_bracket(mem, line, "newline");
		}
		(*bracket)++;
	}
	else if ((*line)[i] == ')')
	{
		if (ft_strchr("(|&;", (*line)[bfor]))
			print_error_bracket(mem, line, ")");
		(*bracket)--;
	}
}
