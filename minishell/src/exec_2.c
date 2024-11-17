/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:36:15 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 09:29:19 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	use_line(t_data_ms *data, char **line)
{
	t_ast_main	*ast;

	ast = NULL;
	add_line_hitory();
	check_error(data, line);
	if (!((*line) == NULL || (*line)[0] == '\n'))
	{
		data->mem_ps = gc_init();
		ast = lexer(data, *line);
		if (ast)
			exec(data, &ast);
		gc_free_all_mem(data->mem_ps);
	}
	if ((*line) == NULL)
		data->cmd = 2;
}

static char	**set_cmd_in_tab(t_data_ms *data, t_subcommand *command,
char ***cmd, int nb)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
	tab = gc_malloc(data->mem, sizeof(char *) * (nb + 1));
	if (command->command[0] == '|')
		tab[i++] = NULL;
	while ((*cmd)[++j])
	{
		tab[i] = gc_strdup(data->mem, get_command_alias(data, (*cmd)[j]));
		gc_free(data->mem_ps, (*cmd)[j]);
		expand(data, data->env, &tab[i++]);
	}
	while (j++ < nb)
		tab[i++] = NULL;
	tab[i] = NULL;
	return (tab);
}

int	set_tab_cmd(t_data_ms *data, t_subcommand *command, char ***tab)
{
	char	**cmd;
	int		i;

	i = 0;
	if (!command->command)
	{
		*tab = gc_malloc(data->mem, sizeof(char *) * 2);
		(*tab)[0] = NULL;
		(*tab)[1] = NULL;
		return (1);
	}
	cmd = split_parse(data->mem_ps, command->command, '|');
	while (cmd[i])
		i++;
	if (command->command[0] == '|')
		i++;
	if (command->command[ft_strlen(command->command) - 1] == '|')
		i++;
	(*tab) = set_cmd_in_tab(data, command, &cmd, i);
	gc_free(data->mem_ps, cmd);
	return (i);
}

static void	setupt_skip_bracket(t_ast **ast, int *open_brackets, int left)
{
	t_ast	*current;

	(*open_brackets) = 1;
	if ((*ast)->left)
	{
		if (left)
			current = (*ast)->left;
		else
			current = *ast;
		while (current && (*open_brackets) > 0)
		{
			current = current->left;
			if (current && current->command->bracket == BRACKET_OPEN)
				(*open_brackets) += current->command->num_bracket;
			else if (current && current->command->bracket == BRACKET_CLOSE)
				(*open_brackets) -= current->command->num_bracket;
		}
	}
	*ast = (*ast)->right;
}

void	skip_bracket(t_ast **ast, int left)
{
	t_ast	*current;
	int		open_brackets;

	setupt_skip_bracket(ast, &open_brackets, left);
	while (open_brackets > 0)
	{
		if ((*ast)->command->bracket == BRACKET_OPEN)
			open_brackets += (*ast)->command->num_bracket;
		else if ((*ast)->command->bracket == BRACKET_CLOSE)
			open_brackets -= (*ast)->command->num_bracket;
		if ((*ast)->left && open_brackets > 0)
		{
			current = *ast;
			while (current && open_brackets > 0)
			{
				current = current->left;
				if (current && current->command->bracket == BRACKET_OPEN)
					open_brackets += current->command->num_bracket;
				else if (current && current->command->bracket == BRACKET_CLOSE)
					open_brackets -= current->command->num_bracket;
			}
		}
		if (open_brackets > 0)
			*ast = (*ast)->right;
	}
}
