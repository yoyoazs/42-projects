/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:26:30 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 12:02:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fct_new_line(t_readline *rl)
{
	if (rl->new_line)
	{
		rl->new_line = false;
		if (g_signal != 0)
			write(1, "\n", 1);
	}
	if (rl->dump)
	{
		rl->dump = false;
		if (g_signal != 0)
			write(2, "Quit (core dumped)\n", 19);
	}
}

void	*readline(char *prompt, char **env, t_memory_table *mem, int get)
{
	static t_readline	*rl = NULL;

	if (get)
		return (rl);
	if (rl)
		fct_new_line(rl);
	if (!rl)
		rl = init_readline(mem);
	rl = reset_readline(rl, prompt, env);
	write(1, prompt, ft_strlen(prompt));
	check_input(rl);
	rl->listen = false;
	restore_input_buffering(rl);
	if (rl->input[0] != '\0')
	{
		goto_end_line(rl);
		write(1, "\n", 1);
		return (rl->input);
	}
	return (NULL);
}

void	rl_new_line(t_readline *rl)
{
	while (rl->history->next)
		rl->history = rl->history->next;
	if (rl->listen)
	{
		restore_input_buffering(rl);
		goto_end_line(rl);
		gc_free(rl->mem, rl->input);
		rl->input = gc_strdup(rl->mem, "\n");
		rl->index = 0;
		rl->listen = false;
	}
	else
		rl->new_line = true;
}

void	rl_clear_history(void)
{
	t_readline	*rl;
	t_history	*tmp;

	rl = (t_readline *)readline(NULL, NULL, NULL, 1);
	while (rl->history->next)
		rl->history = rl->history->next;
	while (rl->history)
	{
		tmp = rl->history;
		rl->history = rl->history->prev;
		gc_free(rl->mem, tmp->line);
		gc_free(rl->mem, tmp);
	}
}
