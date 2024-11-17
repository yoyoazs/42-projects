/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 08:52:01 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/09 09:26:14 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include "parsing.h"
# include "libft.h"
# include "pipex.h"
# include "readline.h"

typedef enum e_signal {
	SSIGINT = 130,
	SSIGQUIT = 131,
}	t_signal;

char			*get_prompt(t_data_ms *data);

char			*get_command_alias(t_data_ms *data, char *cmd);

void			exec(t_data_ms *data, t_ast_main **ast);
void			add_line_hitory(void);
int				signal_type(void);
void			rl_new_line(t_readline *rl);
int				get_file(t_data_ms *data, char **file);
t_command		*create_commands(t_data_ms *data);
int				fn_get_len(const char *string, const char *p_pattern);
char			*get_cwd(t_data_ms *data, int basename);
void			set_std(t_data_ms *data, t_subcommand **subcommand);
void			add_std_end(t_data_ms *data,
					t_subcommand *subcommand, int number);
void			add_std(t_data_ms *data, t_subcommand *sbcmd,
					char *name, int *tab);
void			delete_char_forward(t_readline *rl);
int				get_bytes(int unicode, unsigned char *bytes);
void			check_input(t_readline	*rl);
void			goto_end_line(t_readline *rl);
size_t			after_char(t_readline *rl, size_t index);
void			complete_file(t_readline *rl, size_t i);
void			complete_command(t_readline *rl);
void			realloc_input_cmd(t_readline *rl, char **cmds);
void			print_cmd_list(t_readline	*rl, char **cmds, int count);
bool			is_in_command_list(const char *command,
					char **all_commands, int count);
char			*get_dir_path(t_memory_table *mem, char **cmd, size_t *i);
int				set_tab_cmd(t_data_ms *data,
					t_subcommand *command, char ***tab);
char			*std_get_file(t_data_ms *data);
void			skip_bracket(t_ast **ast, int left);
void			print_in_columns(char **strings,
					int count, int column_width, int width);
int				get_max_length(char **strings, int count);
void			free_files(t_readline *rl, int count, char **files, char *tmp);
int				check_part(t_fnmatch *fm, const char *string);
int				last_part(t_fnmatch *fm, const char *string);
int				check_bracket(t_fnmatch *fm, int p, int i, const char *str);
void			*add_file(t_memory_table *mem, t_file **files,
					char *file, unsigned int type);
void			check_file(t_memory_table *mem, t_file **files, char *pa);
size_t			before_word(char **line, size_t i);
size_t			next_word(char **line, size_t i);
void			check_error_redirection(t_memory_table *mem, char **line,
					size_t *i);
void			check_error_bracket(t_memory_table *mem, char **line, size_t i,
					int *bracket);

t_info_ff		*set_ff(t_memory_table *mem, int nb, t_folder **folder,
					t_file **files);
t_readline		*init_readline(t_memory_table *mem);
t_readline		*reset_readline(t_readline *readline, char *prompt, char **env);

//config
void			parse_config_line(t_data_ms *data, char **line);
int				create_config_file(void);
void			init_shell(t_data_ms *data);
t_mem_and_cmd	*set_mem_info(t_memory_table *mem, long int cmd);

char			*transform_to_ansii(t_data_ms *data, char *str);
void			print_error_bracket(t_memory_table *mem, char **line, char *op);

void			handle_non_interactive_mode(void);

extern int	g_signal;

#endif