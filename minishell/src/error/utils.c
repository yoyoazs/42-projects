/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:12:19 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 09:04:32 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_file(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

static void	print_error_quote(t_memory_table *mem, char **line, char quote)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("'\n", 2);
	gc_free(mem, *line);
	*line = NULL;
}

void	check_last_error(t_data_ms *data, int bracket, char quote, char **line)
{
	if (quote != 0 && *line)
		print_error_quote(data->mem, line, quote);
	if (bracket != 0 && *line)
		print_error_bracket(data->mem, line, "(");
}

size_t	before_word(char **line, size_t i)
{
	size_t	j;

	j = 1;
	while (i - j > 0 && (*line)[i - j] == ' ')
		j++;
	return (i - j);
}

size_t	next_word(char **line, size_t i)
{
	size_t	j;

	j = 0;
	while (i + j < (size_t)ft_strlen(*line) - 1 && (*line)[i + j] == ' ')
		j++;
	if (i + j >= ft_strlen(*line))
		return (-1);
	return (i + j);
}
