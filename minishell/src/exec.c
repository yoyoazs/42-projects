/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:53:12 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/08 15:18:45 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_file(t_data_ms *data, char **file)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	expand(data, data->env, file);
	while ((*file)[++i])
	{
		if ((*file)[i] == '\'' || (*file)[i] == '"')
		{
			if ((*file)[i] == quote)
				quote = 0;
			else if (!quote)
				quote = (*file)[i];
		}
		if (!quote && ((*file)[i] == ' ' || (*file)[i] == '\t'))
			return (0);
	}
	return (1);
}

static void	exec_command(t_data_ms *data, t_ast *ast, int result, char **tab)
{
	char	*tmp;

	result = set_tab_cmd(data, ast->command, &tab);
	data->std = ast->command->std;
	tmp = std_get_file(data);
	if (!tmp)
		data->cmd = pipex_exec(data, result, tab, &data->env);
	else
	{
		print_error_file(tmp);
		gc_free(data->mem, tmp);
	}
	while (result >= 0)
	{
		gc_free(data->mem, tab[result]);
		result--;
	}
	gc_free(data->mem, tab);
	while (data->std)
	{
		ast->command->std = ast->command->std->next;
		gc_free(data->mem, data->std->name);
		gc_free(data->mem, data->std);
		data->std = ast->command->std;
	}
}

static void	exec_right(t_data_ms *data, t_ast **ast)
{
	int		result;
	char	**tab;

	result = 0;
	tab = NULL;
	if (data->cmd == 0 || !(*ast)->command->separator)
	{
		exec_command(data, (*ast), result, tab);
		gc_free(data->mem, data->std);
	}
	else if ((*ast)->command->bracket == BRACKET_OPEN)
		skip_bracket(ast, 0);
}

static void	exec_left(t_data_ms *data, t_ast **ast)
{
	t_ast	*current;
	int		result;
	char	**tab;

	result = 0;
	tab = NULL;
	current = (*ast);
	while (current->left && data->cmd != 0)
	{
		exec_command(data, current->left, result, tab);
		current = current->left;
		gc_free(data->mem, data->std);
	}
	if ((*ast)->left->command->bracket == BRACKET_OPEN)
		skip_bracket(ast, 1);
}

void	exec(t_data_ms *data, t_ast_main **ast_main)
{
	t_ast		*crt;
	t_ast_main	*current;

	current = (*ast_main);
	while (current)
	{
		crt = current->ast;
		while (crt)
		{
			exec_right(data, &crt);
			if (crt && crt->left)
				exec_left(data, &crt);
			if (crt)
				crt = crt->right;
		}
		current = current->next;
	}
	ast_main = NULL;
}
