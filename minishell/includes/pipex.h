/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:18:38 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/06 10:12:42 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include "libft.h"
# include "structure.h"
# include <sys/types.h>
# include <sys/stat.h>

// # ifndef BUFFER_SIZE
// #  define BUFFER_SIZE 42
// # endif

typedef struct s_cmd
{
	char			**paths;
	char			***cut;
	char			**right_path;
	int				int_out;
	int				int_in;
	int				op_nb;
	int				change_in;
	int				change_out;
	int				tmp;
	long int		ret;
	int				ac;
	int				pb;
	bool			expand;
	char			*pwd;
	char			*home;
	pid_t			tempid;
	pid_t			*pids;
	t_memory_table	*mem;
	t_alias			**alias;
	t_std			**std;
}	t_cmd;

void			avoid_quote(const char *str, size_t *i);
char			**split(t_memory_table *mem, const char *s, char c);
void			cut_paths(char **env, t_cmd *cmd);
void			cut_cmd_n_paths(char **env, t_cmd *cmd, char **argv, int ac);
void			find_cmd_paths(t_cmd *cmd, int num, int *fds);
void			message_command_fail_n_free(char *prog_name, int *fds);
void			message_command_fail_n_free_dir(char *prog_name, int *fds);
void			free_paths_rightpaths_cut(t_cmd *cmd);
void			free_paths_rightpaths(t_cmd *cmd);
void			closefds(int *fds);
void			close_exit_exec(t_cmd *cmd, int *fds, int exit);
int				wait_commands(t_cmd *cmd, int *fds);
int				error(char *msg, t_cmd *cmd, int *fds, int tmp);
int				error_existence(char *name, t_cmd *cmd);
int				error_permission(char *inf, char *outf, char *name, t_cmd *cmd);
int				error_pipe(t_cmd *cmd, int tmp);
int				error_exec(t_cmd *cmd, int *fds);
void			error_cut_cmd(t_cmd *cmd, int i);
int				access_test(int num, t_cmd *cmd, int *fds, int tmp);
int				wait_commands(t_cmd *cmd, int *fds);
int				without_cmd(t_cmd *cmd, int *fds);
int				redirection(t_cmd *cmd, int *fds);
void			exec_middle_one_cmd(t_cmd *cmd, int *fds, int i, char ***env);
void			exec_last(t_cmd *cmd, int *fds, char ***env);
int				verif_last(t_cmd *cmd, t_std *stack);
void			open_file(t_cmd *cmd, int nb);
void			execution_cmd_or_builtins(t_cmd *cmd, int *fds, char ***env,
					int tmp);
void			crossing_craft_doc(t_cmd *cmd, char ***env);
void			delete_hd_file(t_cmd *cmd);
int				pb_hd(t_cmd *cmd, int *fds);
int				hd_ctrld_msg(char *eof, t_cmd *cmd);
char			*get_from_env(char ***env, char *path_asked);
int long long	verif_long_overf(char *argv);
char			*ft_long_itoa(long long int n);
int				var_exist(char **env, char *key);
void			change_var(char ***env, char *key, char *value,
					t_memory_table *mem);
int				str_is_alphanum(char *arg, int delim);
int				show_all_alias(t_cmd *cmd, int *fds);
int				show_alias(t_cmd *cmd, char *alias, int *fds);
int				builtin_cmd(int num, t_cmd *cmd, int *fds, char ***env);
int				builtin_test_one(int num, t_cmd *cmd, int *fds, char ***env);
int				run_pwd(int *fds, char **av, t_cmd *cmd);
int				run_echo(char **av, int *fds, t_cmd *cmd);
int				run_cd(t_cmd *cmd, char **argv, char ***env);
int				run_env(char **env, int *fds, char **argv, t_cmd *cmd);
int				run_unset(char **args, char ***env, t_cmd *cmd);
int				run_exit(char **argv, t_cmd *cmd, int *fds);
int				run_export(t_cmd *cmd, char ***env, char **argv, int *fds);
int				run_alias(t_cmd *cmd, char **argv, int *fds);
int				file_is_full(char *to_write, t_cmd *cmd);

#endif