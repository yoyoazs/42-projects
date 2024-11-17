/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:26:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 10:00:20 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_commands(t_data_ms *data)
{
	t_command	*commands;

	commands = gc_malloc(data->mem_ps, sizeof(t_command));
	commands->next = NULL;
	commands->subcommands = gc_malloc(data->mem_ps, sizeof(t_subcommand));
	commands->subcommands->next = NULL;
	commands->subcommands->std = NULL;
	commands->subcommands->command = NULL;
	commands->subcommands->separator = NULL;
	commands->subcommands->bracket = NONE;
	commands->subcommands->num_bracket = 0;
	set_std(data, &commands->subcommands);
	return (commands);
}

t_subcommand	*add_subcommand(t_data_ms *data, t_subcommand *current)
{
	t_subcommand	*new;

	new = gc_malloc(data->mem_ps, sizeof(t_subcommand));
	new->next = NULL;
	new->std = NULL;
	new->command = NULL;
	new->bracket = NONE;
	new->separator = NULL;
	new->num_bracket = 0;
	set_std(data, &new);
	current->next = new;
	return (new);
}
