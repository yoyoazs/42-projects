/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 02:09:38 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 14:46:37 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_operator(t_data_ms *data, t_parser *p)
{
	int	tab[4];

	if (p->current->type == TOKEN_OPERATOR)
	{
		tab[3] = p->number;
		tab[2] = 0;
		tab[0] = 0;
		if (p->current->value[0] == '>')
		{
			if (p->current->value[1])
				tab[0] = 1;
			tab[1] = 0;
		}
		else if (p->current->value[0] == '<')
		{
			if (p->current->value[1])
				tab[2] = 1;
			tab[1] = 1;
		}
		add_std(data, p->current_scmd, p->current->next->value, tab);
		p->current = p->current->next->next;
		return (1);
	}
	return (0);
}

static void	parse_separator(t_data_ms *data, t_parser *p)
{
	t_command	*news_cmd;

	add_std_end(data, p->current_scmd, p->number);
	if (p->current->value[0] == ';')
	{
		news_cmd = create_commands(data);
		p->current = p->current->next;
		p->current_scmd = news_cmd->subcommands;
		p->cmds = p->last_cmd;
		while (p->cmds->next)
			p->cmds = p->cmds->next;
		p->cmds->next = news_cmd;
		p->cmds = news_cmd;
	}
	else
	{
		if (p->in_bracket && p->current_scmd->bracket == NONE)
			p->current_scmd->bracket = BRACKET_IN;
		p->current_scmd = add_subcommand(data, p->current_scmd);
		p->current_scmd->separator = gc_strdup(data->mem_ps, p->current->value);
		p->current = p->current->next;
	}
	p->number = 0;
}

static int	parse_bracket(t_parser *p)
{
	if (p->current->type == TOKEN_BRACKET)
	{
		if (p->current->value[0] == '(')
		{
			p->current_scmd->bracket = BRACKET_OPEN;
			p->current_scmd->num_bracket++;
		}
		else if (p->current_scmd->bracket == NONE
			|| p->current_scmd->bracket == BRACKET_CLOSE)
		{
			p->current_scmd->bracket = BRACKET_CLOSE;
			p->current_scmd->num_bracket++;
		}
		else
			p->current_scmd->bracket = NONE;
		p->in_bracket = !p->in_bracket;
		p->current = p->current->next;
		return (1);
	}
	return (0);
}

static void	update_subcommad(t_data_ms *data, t_parser *p)
{
	if (p->current->value != NULL)
	{
		p->current_scmd->command = gc_strjoin(data->mem_ps,
				p->current_scmd->command, " ");
		p->current_scmd->command = gc_strjoin(data->mem_ps,
				p->current_scmd->command, p->current->value);
	}
}

t_ast_main	*parser(t_token *tokens, t_data_ms *data)
{
	t_parser	*p;
	t_command	*tmp;

	p = init_parser(data, tokens);
	while (p->current && p->current->type != TOKEN_END)
	{
		if (is_sep_not_pipe(p))
		{
			parse_separator(data, p);
			continue ;
		}
		else if (parse_bracket(p) || parse_operator(data, p))
			continue ;
		else if (p->current->value[0] == '|' && !p->current->value[1])
			p->number++;
		update_subcommad(data, p);
		p->current = p->current->next;
	}
	add_std_end(data, p->current_scmd, p->number);
	if (p->in_bracket && p->current_scmd->bracket == NONE)
		p->current_scmd->bracket = BRACKET_CLOSE;
	free_tokens(data, tokens);
	tmp = p->last_cmd;
	gc_free(data->mem, p);
	return (ast_from_tokens(data, tmp));
}
