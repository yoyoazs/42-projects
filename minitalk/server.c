/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:08:59 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/05 11:43:09 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	error_handler(char *str)
{
	ft_printf("\x1B[31m[Server/ERROR]: %s.\x1B[0m\n", str);
	exit(1);
}

void	send_signal(pid_t pid, int sig, char *str)
{
	if (sig == SIGUSR1)
	{
		if (kill(pid, sig) == -1)
			error_handler("KILL SIGUSR1");
	}
	else if (sig == SIGUSR2)
	{
		if (kill(pid, sig) == -1)
			error_handler("KILL SIGUSR2");
	}
	free(str);
}

void	end_signal(char **str, siginfo_t *info, int *end)
{
	if (!(*end))
	{
		send_signal(info->si_pid, SIGUSR1, NULL);
		return ;
	}
	*end = 0;
	ft_printf("%s\n", *str);
	if (ft_strlen(*str) != 4 || ft_strncmp(*str, "exit", 4) != 0)
	{
		ft_printf("\x1B[90m[Server] - Waitting for new message...\x1B[0m\n");
		send_signal(info->si_pid, SIGUSR2, (*str));
		*str = NULL;
		return ;
	}
	ft_printf("\n\x1B[92m[SERVER] - Received 'exit' command.\x1B[0m\n");
	ft_printf("\x1B[91m[SERVER] - Shutdown...\x1B[0m\n");
	send_signal(info->si_pid, SIGUSR2, (*str));
	exit(0);
}

void	signal_handler(int sig, siginfo_t *info, void *ctx)
{
	static char	val = 0;
	static int	bit = 1;
	static char	*str = NULL;
	static int	end = 0;

	if (sig == SIGUSR2)
		val += bit;
	if (bit == 1 && str == NULL)
		ft_printf("\n\x1B[92m[SERVER] - Receive new message.\x1B[0m\n");
	bit *= 2;
	if (bit == 256)
	{
		bit = 1;
		if (val != 0)
		{
			str = ft_strjoin(str, &val);
			if (!str)
				error_handler("STRJOIN");
		}
		else
			end = 1;
		val = 0;
	}
	end_signal(&str, info, &end);
	(void)ctx;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &signal_handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	pid = getpid();
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		error_handler("SIGACTION");
	ft_printf("\x1B[92m[Server] - PID: %d\x1B[0m\n", pid);
	ft_printf("\x1B[90m[Server] - Waitting for message...\x1B[0m\n");
	while (1)
		pause();
	return (0);
}
