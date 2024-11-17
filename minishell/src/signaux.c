/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 11:39:01 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/06 11:28:36 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_signal(int sig, siginfo_t *info, void *context)
{
	t_readline	*rl;

	rl = readline(NULL, NULL, NULL, true);
	if (sig == SIGINT)
	{
		rl_new_line(rl);
		g_signal = SSIGINT;
	}
	else if (sig == SIGQUIT && !rl->listen)
	{
		rl->dump = true;
		g_signal = SSIGQUIT;
	}
	(void)info;
	(void)context;
}

int	signal_type(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_signal;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	signal(SIGWINCH, handle_sigwinch);
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
		return (0);
	return (1);
}
