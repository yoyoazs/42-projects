/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:11:43 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/09 09:54:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirection_error(t_memory_table *mem, char *error, char **line)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("'\n", 2);
	gc_free(mem, *line);
	*line = NULL;
}

static void	check_error_redirection_name(t_memory_table *mem, int num, char c,
char **line)
{
	if (num == 3 && c == '>')
		redirection_error(mem, ">", line);
	else if (num > 3 && c == '>')
		redirection_error(mem, ">>", line);
	else if (num == 3 && c == '<')
		redirection_error(mem, "<", line);
	else if (num >= 3 && c == '<')
		redirection_error(mem, "<<", line);
}

static size_t	next_word_redirection(char **line, size_t i, char redirection)
{
	size_t	j;

	j = i;
	while (j < ft_strlen(*line) - 1 && (*line)[j] == redirection)
		j++;
	while (j < ft_strlen(*line) - 1 && (*line)[j + 1] != ' ')
		j++;
	return (j);
}

void	check_error_redirection(t_memory_table *mem, char **line, size_t *i)
{
	int			num;
	int			next;
	const int	before = before_word(line, (*i));
	char		c;

	num = 1;
	c = (*line)[(*i)];
	while ((*i)++ < ft_strlen(*line) && (*line)[(*i)] == c)
		num++;
	(*i)--;
	next = next_word_redirection(line, (*i) + num - 1, c);
	if (ft_strchr("<>)", (*line)[before]))
		check_error_redirection_name(mem, num, c, line);
	if (num <= 2 && *line && (next == -1 || !(*line)[next]
		|| (*line)[next] == ' '))
		redirection_error(mem, "newline", line);
	else if (*line)
		check_error_redirection_name(mem, num, c, line);
	if (*line && (*line)[next] == '#')
		redirection_error(mem, "newline", line);
}
