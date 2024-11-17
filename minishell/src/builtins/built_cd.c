/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 09:52:22 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/05 17:36:59 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

static void	change_var_cd(char ***env, char *key, char *value,
t_memory_table *mem)
{
	const int	pos = var_exist(*env, key);

	if (!ft_strlen(value))
		return ;
	if (pos == -1)
		return ;
	gc_free(mem, (*env)[pos]);
	(*env)[pos] = gc_strjoin(mem, key, "=");
	(*env)[pos] = gc_strjoin(mem, (*env)[pos], value);
}

static int	change(char *path, t_cmd *cmd, char ***env)
{
	int	pos;

	pos = var_exist(*env, "OLDPWD");
	if (!chdir(path))
	{
		cmd->pwd = getcwd(NULL, 0);
		if (var_exist(*env, "PWD") == -1 && pos != -1)
		{
			gc_free(cmd->mem, (*env)[pos]);
			(*env)[pos] = gc_strdup(cmd->mem, "OLDPWD");
		}
		else
		{
			change_var_cd(env, gc_strdup(cmd->mem, "OLDPWD"),
				gc_strdup(cmd->mem, get_from_env(env, "PWD")), cmd->mem);
			change_var_cd(env, gc_strdup(cmd->mem, "PWD"), cmd->pwd, cmd->mem);
		}
		return (free(cmd->pwd), 1);
	}
	return (0);
}

int	set_directory(char *path, t_cmd *cmd, char ***env)
{
	if (change(path, cmd, env))
		return (1);
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	cmd->pb = 1;
	if (access(path, F_OK))
	{
		write(2, ": No such file or directory", 28);
		cmd->pb = 127;
	}
	else if (access(path, R_OK | X_OK))
		write(2, ": Permission denied", 20);
	else
		write(2, ": Not a directory", 18);
	write(2, "\n", 1);
	return (cmd->ret = 1);
}

int	s_path(t_cmd *cmd, char ***env, char **argv)
{
	char	*tmp;

	if (!ft_strncmp(argv[1], "-", 1) && !argv[1][1])
	{
		if (var_exist(*env, "OLDPWD") == -1)
			return (write(2, "minishell: cd: OLDPWD not set\n", 30),
				cmd->ret = 1);
		tmp = get_from_env(env, "OLDPWD");
		if (tmp)
			set_directory(tmp, cmd, env);
		return (cmd->ret = 1);
	}
	return (set_directory(argv[1], cmd, env));
}

int	run_cd(t_cmd *cmd, char **argv, char ***env)
{
	cmd->home = get_from_env(env, "HOME");
	if (argv && argv[1] && argv[2])
		return (write(2, "cd: too many arguments\n", 24),
			cmd->ret = 1);
	if (!argv[1] || (!ft_strncmp(argv[1], "--", 2) && !argv[1][2]))
	{
		if (!cmd->home)
			return (write(2, "cd: HOME not set\n", 18), 1);
		return (set_directory(cmd->home, cmd, env));
	}
	return (s_path(cmd, env, argv));
}
