/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 10:48:52 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:01:23 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_history(t_readline *rl, char *line, bool to_save)
{
	t_history	*new;

	while (rl->history && rl->history->next)
		rl->history = rl->history->next;
	if (rl->history && !ft_strcmp(line, rl->history->line))
		return ;
	new = (t_history *)gc_malloc(rl->mem, sizeof(t_history));
	new->line = gc_strdup(rl->mem, line);
	new->next = NULL;
	new->to_save = to_save;
	if (rl->history == NULL)
	{
		rl->history = new;
		rl->history->prev = NULL;
	}
	else
	{
		rl->history->next = new;
		new->prev = rl->history;
		rl->history = new;
	}
}

void	add_line_hitory(void)
{
	t_readline	*rl;

	rl = readline(NULL, NULL, NULL, true);
	if (rl && rl->input && rl->input[0] != '\n')
	{
		while (rl->history->next)
			rl->history = rl->history->next;
		if (!rl->history->prev
			|| ft_strcmp(rl->input, rl->history->prev->line) != 0)
		{
			gc_free(rl->mem, rl->history->line);
			rl->history->line = gc_strdup(rl->mem, rl->input);
			add_to_history(rl, "", true);
		}
		else
		{
			gc_free(rl->mem, rl->history->line);
			rl->history->line = gc_strdup(rl->mem, "");
		}
	}
}
