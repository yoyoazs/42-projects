/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:43:57 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/04/16 17:27:44 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include "libft.h"
# include "structure.h"

typedef enum e_bracket
{
	NONE,
	BRACKET_OPEN,
	BRACKET_IN,
	BRACKET_CLOSE
}	t_bracket;

typedef enum e_token_type
{
	TOKEN_ARGUMENT,
	TOKEN_OPERATOR,
	TOKEN_SEPARATOR,
	TOKEN_BRACKET,
	TOKEN_STRING,
	TOKEN_END
}	t_token_type;

typedef struct s_dollar
{
	char	*var;
	int		len;
}	t_dollar;

typedef struct s_folder
{
	char			*name;
	int				nb_folders;
	struct s_folder	*next;
}	t_folder;

typedef struct s_file
{
	char			*name;
	unsigned int	type;
	struct s_file	*next;
}	t_file;

typedef struct s_info_ff
{
	int			nb;
	t_folder	**folder;
	t_file		**files;
	char		*name;
}	t_info_ff;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_subcommand
{
	char				*command;
	char				*separator;
	t_std				*std;
	t_bracket			bracket;
	int					num_bracket;
	struct s_subcommand	*next;
}	t_subcommand;

typedef struct s_command
{
	t_subcommand		*subcommands;
	struct s_command	*next;
}	t_command;

typedef struct s_ast
{
	t_subcommand	*command;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_ast_main
{
	t_ast				*ast;
	struct s_ast_main	*next;
}	t_ast_main;

typedef struct s_fnmatch
{
	int		s;
	int		p;
	int		escape;
	int		loop;
	char	*p_pattern;
}	t_fnmatch;

typedef struct s_parser
{
	t_token			*current;
	t_command		*cmds;
	t_command		*last_cmd;
	t_subcommand	*current_scmd;
	int				number;
	bool			in_bracket;
}	t_parser;

typedef struct s_data_ms
{
	t_memory_table	*mem;
	t_memory_table	*mem_ps;
	t_alias			*alias;
	t_std			*std;
	long int		cmd;
	bool			in_hd;
	char			**env;
}	t_data_ms;

int				pipex_exec(t_data_ms *data, int argc, char **argv, char ***env);

void			free_tab(t_memory_table *mem, char **tab);
char			*ft_strtok(char *str, const char *delim);
t_ast_main		*lexer(t_data_ms *data, char *line);
char			*get_env_var(t_memory_table *mem, char **env, char *name);

//TOKENS
t_token			*create_token(t_data_ms *data, t_token *tokens,
					char *value, t_token_type type);
void			free_tokens(t_data_ms *data, t_token *tokens);
t_subcommand	*add_subcommand(t_data_ms *data, t_subcommand *current);
t_ast_main		*parser(t_token *tokens, t_data_ms *data);
t_ast_main		*ast_from_tokens(t_data_ms *data, t_command *command);
void			expand(t_data_ms *data, char **env, char **subcommand);
void			handle_dollar(t_mem_and_cmd *info, char **env,
					char **cmd, size_t *i);

//WILDCARD
void			handle_wildcard(t_memory_table *mem,
					t_memory_table *mem_ps, char **cmd, size_t *i);
void			add_folder(t_memory_table *mem, t_folder **folders,
					char *name, int i);
int				ft_fnmatch(t_memory_table *mem, const char *pattern,
					const char *string);
char			*get_prefix(t_memory_table *mem, char **cmd, size_t len);
void			get_files_multifolder(t_memory_table *mem, t_file **files,
					char *dir_path, char *prefix);
char			*get_files_string(t_memory_table *mem, t_file *files);
void			check_error(t_data_ms *data, char **line);

t_parser		*init_parser(t_data_ms *data, t_token *tokens);
void			use_line(t_data_ms *data, char **line);
bool			is_empty(char *str);
bool			is_sep_not_pipe(t_parser *p);

char			**split_parse(t_memory_table *mem, const char *s, char c);
void			check_last_error(t_data_ms *data, int bracket, char quote,
					char **line);
void			print_error_file(char *file);
int				ft_strcasecmp(const char *s1, const char *s2);

void			add_quote(t_memory_table *mem, char **var);

#endif