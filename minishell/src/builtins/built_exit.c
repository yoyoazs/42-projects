/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:11:48 by npigeon           #+#    #+#             */
/*   Updated: 2024/04/22 11:11:48 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

int	verif_nb(char *argv)
{
	int	j;

	j = 1;
	if ((!((argv[0] <= '9' && argv[0] >= '0') || argv[0] == '+'
				|| argv[0] == '-')) || ((argv[0] == '+' || argv[0] == '-')
			&& !('0' <= argv[1] && argv[1] <= '9')))
		return (0);
	while (argv[j])
	{
		if (!((argv[j] <= '9' && argv[j] >= '0')))
			return (0);
		j++;
	}
	return (1);
}

void	exit_num_arg_required(int retour, char *contenu, t_cmd *cmd, int *fds)
{
	write(2, "exit: ", 6);
	write(2, contenu, ft_strlen(contenu));
	write(2, ": numeric argument required\n", 28);
	if (cmd->change_in)
		close(cmd->int_in);
	if (cmd->change_out)
		close(cmd->int_out);
	closefds(fds);
	if (cmd->tmp == -1)
		save_historic();
	else
		close(cmd->tmp);
	gc_exit(retour);
}

void	exit_ok(int retour, t_cmd *cmd, int *fds)
{
	if (cmd->change_in)
		close(cmd->int_in);
	if (cmd->change_out)
		close(cmd->int_out);
	closefds(fds);
	if (cmd->tmp == -1)
	{
		write(2, "exit\n", 5);
		save_historic();
	}
	else
		close(cmd->tmp);
	gc_exit(retour);
}

static int	fct_exit(t_cmd *cmd, char *av_one, int *fds)
{
	if (verif_nb(av_one))
	{
		if (verif_long_overf(av_one))
		{
			if (ft_atoi(av_one) >= 0)
				exit_ok(ft_atoi(av_one) % 256, cmd, fds);
			else
				exit_ok(256 + ft_atoi(av_one) % 256, cmd, fds);
		}
		else
			exit_num_arg_required(2, av_one, cmd, fds);
	}
	else
		exit_num_arg_required(2, av_one, cmd, fds);
	return (1);
}

int	run_exit(char **argv, t_cmd *cmd, int *fds)
{
	if (argv && argv[0] && argv[1] && argv[2])
	{
		if (verif_nb(argv[1]))
		{
			write(2, "exit: too many arguments\n", 26);
			return (cmd->ret = 1);
		}
		else
			exit_num_arg_required(2, argv[1], cmd, fds);
	}
	else if (argv && argv[1])
		fct_exit(cmd, argv[1], fds);
	else
		exit_ok(cmd->ret, cmd, fds);
	return (cmd->ret = 1);
}
