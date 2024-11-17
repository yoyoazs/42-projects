/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:30:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 09:15:37 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*create_ast_node(t_data_ms *data, t_subcommand *command)
{
	t_ast	*node;

	node = (t_ast *)gc_malloc(data->mem_ps, sizeof(t_ast));
	node->command = command;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void	add_ast(t_data_ms *data, t_ast **ast, t_subcommand *sbcmd,
bool right)
{
	t_ast	*new_node;
	t_ast	*current;

	new_node = create_ast_node(data, sbcmd);
	current = (*ast);
	if ((*ast) == NULL)
		(*ast) = new_node;
	else if (right)
	{
		while (current->right)
			current = current->right;
		current->right = new_node;
	}
	else if (!right)
	{
		while (current->right)
			current = current->right;
		while (current->left)
			current = current->left;
		current->left = new_node;
	}
}

static void	subcommad_loop(t_data_ms *data, t_subcommand *sbcmd,
t_ast_main **cur)
{
	t_ast	*last_right;	

	while (sbcmd)
	{
		last_right = (*cur)->ast;
		while (sbcmd && sbcmd->separator
			&& sbcmd->separator[0] == '|' && sbcmd->separator[1] == '|')
		{
			add_ast(data, &(*cur)->ast, sbcmd, false);
			sbcmd = sbcmd->next;
		}
		if (!sbcmd)
			break ;
		(*cur)->ast = last_right;
		add_ast(data, &(*cur)->ast, sbcmd, true);
		sbcmd = sbcmd->next;
	}
}

t_ast_main	*ast_from_tokens(t_data_ms *data, t_command *cmds)
{
	t_ast_main		*main;
	t_ast_main		*current;
	t_subcommand	*c_subcmd;
	t_command		*current_cmd;

	main = NULL;
	if (!cmds || !cmds->subcommands)
		return (NULL);
	current_cmd = cmds;
	while (current_cmd)
	{
		current = gc_malloc(data->mem_ps, sizeof(t_ast_main));
		current->ast = NULL;
		current->next = NULL;
		c_subcmd = current_cmd->subcommands;
		subcommad_loop(data, c_subcmd, &current);
		if (main)
			main->next = current;
		else
			main = current;
		current_cmd = current_cmd->next;
		gc_free(data->mem_ps, cmds);
		cmds = current_cmd;
	}
	return (main);
}
