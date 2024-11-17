/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:09:05 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/05 11:25:05 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft.h"

void	error_handler(char *str)
{
	ft_printf("\x1B[31m[Client/ERROR]: %s\x1B[0m\n", str);
	exit(1);
}

void	send_terminator(int pid)
{
	static int	i = 0;

	if (i++ < 8)
	{	
		if (kill(pid, SIGUSR1) == -1)
			error_handler("KILL");
	}
}

void	send_signal(char *str, int pid)
{
	static char	*str_bis = 0;
	static int	bit = -1;

	if (str)
		str_bis = str;
	if (str_bis[++bit / 8])
	{
		if (str_bis[bit / 8] & (1 << (bit % 8)))
		{
			if (kill(pid, SIGUSR2) == -1)
				error_handler("KILL");
		}
		else if (kill(pid, SIGUSR1) == -1)
			error_handler("KILL");
		return ;
	}
	send_terminator(pid);
}

void	receipt(int sig, siginfo_t *info, void *ctx)
{
	if (sig == SIGUSR1)
		send_signal(NULL, info->si_pid);
	else if (sig == SIGUSR2)
	{
		ft_printf("\x1B[90m[Client] - Message sent successfully.\x1B[0m\n");
		exit(EXIT_SUCCESS);
	}
	(void)ctx;
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &receipt;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		error_handler("SIGACTION");
	if (argc != 3)
		error_handler("Wrong format './client <PID> <MESSAGE>'.");
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
		error_handler("Wrong PID.");
	ft_printf("\x1B[92m[Client] - PID: %d\x1B[0m\n", pid);
	send_signal(argv[2], pid);
	ft_printf("\x1B[90m[Client] - Message send.\x1B[0m\n");
	while (1)
		pause();
	return (0);
}
