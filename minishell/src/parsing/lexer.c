/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:27:35 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 08:48:20 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_quotes(t_data_ms *data, t_token **tokens, char **line, int *i)
{
	char	quote_char;
	int		close_quote;

	quote_char = (*line)[(*i)++];
	close_quote = 0;
	while ((*line)[*i])
	{
		if ((*line)[*i] == quote_char && !close_quote)
			close_quote = 1;
		if ((*line)[*i] == ' ' && close_quote)
			break ;
		if (ft_strchr(" ;|<>()", ((*line)[*i])) && close_quote)
		{
			(*i)--;
			break ;
		}
		if (((*line)[*i] == '"' || (*line)[*i] == '\'') && close_quote)
			quote_char = (*line)[*i];
		(*i)++;
	}
	if (!(*line)[*i])
		(*i)--;
	*tokens = create_token(data, *tokens,
			gc_strndup(data->mem_ps, &(*line)[0], *i + 1), TOKEN_STRING);
	*line += *i + 1;
}

static void	lexer_operator(t_data_ms *data, t_token **tokens, char **line,
int *i)
{
	char	*operator;

	if (*i == 0 && (*line)[*i] == ' ')
	{
		(*line)++;
		*i = -1;
		return ;
	}
	if (*i > 0)
		*tokens = create_token(data, *tokens,
				gc_strndup(data->mem_ps, *line, *i), TOKEN_ARGUMENT);
	if ((*line)[*i] != ' ')
	{
		operator = gc_strndup(data->mem_ps, &(*line)[*i], 1);
		if (operator[0] == ';' || operator[0] == '|')
			*tokens = create_token(data, *tokens, operator, TOKEN_SEPARATOR);
		else if (operator[0] == '(' || operator[0] == ')')
			*tokens = create_token(data, *tokens, operator, TOKEN_BRACKET);
		else
			*tokens = create_token(data, *tokens, operator, TOKEN_OPERATOR);
	}
	*line += (*i) + 1;
	*i = -1;
}

static void	lexer_add_token(t_data_ms *data, t_token **tokens, char **line,
int *i)
{
	if ((*i) > 0)
		*tokens = create_token(data, *tokens,
				gc_strndup(data->mem_ps, (*line), *i), TOKEN_ARGUMENT);
	if ((*line)[(*i)] == '&' || (*line)[*i] == '|')
		*tokens = create_token(data, *tokens,
				gc_strndup(data->mem_ps, &(*line)[*i], 2), TOKEN_SEPARATOR);
	else
		*tokens = create_token(data, *tokens,
				gc_strndup(data->mem_ps, &(*line)[*i], 2), TOKEN_OPERATOR);
	*line += *i + 2;
	*i = -1;
}

static int	lexer_boucle(t_data_ms *data, t_token **tokens, char **line, int *i)
{
	if ((*line)[*i] == '"' || (*line)[*i] == '\'')
	{
		lexer_quotes(data, tokens, line, i);
		*i = -1;
	}
	else if (((*line)[*i] == '&' && (*line)[*i + 1] == '&')
		|| ((*line)[*i] == '|' && (*line)[*i + 1] == '|')
		|| ((*line)[*i] == '<' && (*line)[*i + 1] == '<')
		|| ((*line)[*i] == '>' && (*line)[*i + 1] == '>'))
		lexer_add_token(data, tokens, line, i);
	else if (ft_strchr(" ;|<>()", (*line)[*i]))
		lexer_operator(data, tokens, line, i);
	else if ((*line)[*i] == '#' && (!(*line)[*i - 1] || (*line)[*i - 1] == ' '))
	{
		if ((*i) > 0)
			*tokens = create_token(data, *tokens,
					gc_strndup(data->mem_ps, (*line), *i), TOKEN_ARGUMENT);
		return (1);
	}
	return (0);
}

t_ast_main	*lexer(t_data_ms *data, char *line)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = -1;
	while (i < (int)ft_strlen(line) && line[++i])
	{
		if (lexer_boucle(data, &tokens, &line, &i))
			break ;
	}
	if (i > 0 && line[i] != '#')
		tokens = create_token(data, tokens,
				gc_strndup(data->mem_ps, line, i), TOKEN_ARGUMENT);
	tokens = create_token(data, tokens, NULL, TOKEN_END);
	return (parser(tokens, data));
}
