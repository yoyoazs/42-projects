/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:32:53 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 13:36:45 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <termios.h>
# include <dirent.h>
# include "libft.h"

enum
{
	UP_KEY = 65,
	DOWN_KEY = 66,
	RIGHT_KEY = 67,
	LEFT_KEY = 68,
	CTRL_RIGHT = 167,
	CTRL_LEFT = 168,
	HOME = 72,
	END = 70
};

typedef struct s_history
{
	char				*line;
	bool				to_save;
	struct s_history	*next;
	struct s_history	*prev;
}	t_history;

typedef struct s_cursor
{
	int		x;
	int		y;
}	t_cursor;

typedef struct s_readline
{
	bool			listen;
	char			*input;
	char			*prompt;
	int				cmd;
	size_t			index;
	size_t			len_prompt;
	size_t			max_len_input;
	t_cursor		*last_dim;
	t_cursor		*cursor;
	t_cursor		*start;
	char			**env;
	bool			new_line;
	bool			dump;
	struct termios	orig_term;
	t_history		*history;
	t_memory_table	*mem;
}	t_readline;

//BUFFER
int		set_unbuffered_input(t_readline *readline);
void	restore_input_buffering(t_readline *rl);

//HISTORY
void	history(t_readline *rl, int direction);
void	add_to_history(t_readline *rl, char *line, bool to_save);
void	get_historic(t_readline *rl);
void	save_historic(void);
void	rl_clear_history(void);

//CURSOR
void	cursor_gestion(int direction, t_readline *rl);
void	get_cursor_pos(t_cursor *c);

//UTILS
size_t	len_without_esc(const char *str);
size_t	len_string_8(const char *str, size_t index);
void	reset_screen(t_readline *rl);
size_t	get_string_len_in_terminal(const char *str, size_t max,
			size_t terminal_width);
void	update_display(t_readline *rl, unsigned char *bytes, int len);

//AUTOCOMPLETE
void	auto_completion(t_readline *rl);
int		read_key(void);
void	insert_char(t_readline *rl, int unicode, int width);
void	delete_char(t_readline *rl);
void	*readline(char *prompt, char **env, t_memory_table *mem, int get);

//SIGWINCH
void	handle_sigwinch(int sig);
void	reset_ligne(t_readline *rl);

int		get_terminal_width(void);
int		get_terminal_height(void);

char	*get_prefix_file(t_memory_table *mem, char **cmd, size_t len);
void	bubble_sort(char **strings, int count);

#endif