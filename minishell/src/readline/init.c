/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:27:06 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 13:36:01 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_readline	*init_readline(t_memory_table *mem)
{
	t_readline	*readline;

	readline = (t_readline *)gc_malloc(mem, sizeof(t_readline));
	readline->last_dim = (t_cursor *)gc_malloc(mem, sizeof(t_cursor));
	readline->cursor = (t_cursor *)gc_malloc(mem, sizeof(t_cursor));
	readline->start = (t_cursor *)gc_malloc(mem, sizeof(t_cursor));
	readline->new_line = false;
	readline->history = NULL;
	readline->mem = mem;
	readline->dump = false;
	get_historic(readline);
	add_to_history(readline, "", true);
	return (readline);
}

t_readline	*reset_readline(t_readline *readline, char *prompt, char **env)
{
	gc_malloc(readline->mem, 16 * sizeof(char));
	readline->input = (char *)gc_malloc(readline->mem, 16 * sizeof(char));
	readline->input[0] = '\0';
	readline->index = 0;
	readline->listen = true;
	readline->prompt = prompt;
	readline->env = env;
	readline->len_prompt = len_without_esc(prompt);
	readline->max_len_input = 16;
	readline->last_dim->x = get_terminal_width();
	readline->last_dim->y = get_terminal_height();
	set_unbuffered_input(readline);
	get_cursor_pos(readline->start);
	readline->cursor->x = readline->start->x + readline->len_prompt - 1;
	readline->cursor->y = readline->start->y;
	return (readline);
}
