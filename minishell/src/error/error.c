/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:14:22 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/05 13:14:22 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_caracter(char **line, size_t i, char c)
{
	const int	before = before_word(line, i);
	int			next;
	size_t		j;

	j = 0;
	while (i + j < ft_strlen(*line) && (*line)[i + j] == c)
		j++;
	next = next_word(line, i + j);
	if (before < 0)
		return (1);
	if (ft_strchr("<>|;", (*line)[before]))
		return (1);
	if ((*line)[before] == '&' && (*line)[before - 1] == '&')
		return (1);
	if ((!(*line)[next] || (*line)[next] == ' '))
		return (1);
	if ((*line)[next] == '#')
		return (1);
	return (0);
}

static void	check_operator(t_memory_table *mem, char **line, size_t *i)
{
	const int	error = check_invalid_caracter(line, *i, (*line)[*i]);

	if (error)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd((*line)[*i], 2);
		if ((*line)[*i] == (*line)[*i + 1])
			ft_putchar_fd((*line)[*i], 2);
		ft_putstr_fd("'\n", 2);
		gc_free(mem, *line);
		*line = NULL;
	}
	if (*line && (*line)[*i] == (*line)[*i + 1])
		(*i)++;
}

static int	check_error_loop(t_memory_table *mem, char **line, char *quote,
size_t *i)
{
	if (*line && (*line)[*i] == '#' && (!(*line)[*i - 1]
		|| (*line)[*i - 1] == ' ') && !(*quote))
		return (0);
	if (*line && ((*line)[*i] == '\'' || (*line)[*i] == '"') && !(*quote))
	{
		(*quote) = (*line)[*i];
		return (1);
	}
	else if (*line && (*quote) && (*line)[*i] != (*quote))
		return (1);
	else if (*line && (*quote))
	{
		(*quote) = 0;
		return (1);
	}
	else if (*line && ft_strchr("<>", (*line)[*i]) && !(*quote))
	{
		check_error_redirection(mem, line, i);
		return (1);
	}
	return (2);
}

void	check_error(t_data_ms *data, char **line)
{
	size_t			i;
	char			quote;
	int				bracket;
	int				r;
	const size_t	len = ft_strlen(*line);

	i = -1;
	bracket = 0;
	quote = 0;
	if (*line == NULL)
		return ;
	while (*line && len > ++i)
	{
		r = check_error_loop(data->mem, line, &quote, &i);
		if (r == 1)
			continue ;
		if (r == 0)
			break ;
		else if (*line && ft_strchr("()", (*line)[i]) && !quote)
			check_error_bracket(data->mem, line, i, &bracket);
		else if (*line && ft_strchr("&|;", (*line)[i]) && !quote)
			check_operator(data->mem, line, &i);
	}
	check_last_error(data, bracket, quote, line);
}
