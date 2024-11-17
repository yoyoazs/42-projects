/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:02:44 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/06 08:42:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_data_ms *data)
{
	int		fd;
	char	*line;

	fd = open(".msh_config", O_RDWR | O_APPEND, 0666);
	if (fd == -1)
		fd = create_config_file();
	if (fd == -1)
		return ;
	data->mem_ps = gc_init();
	line = gc_get_next_line(data->mem_ps, fd);
	while (line)
	{
		if (ft_strlen(line) == 0 || is_empty(line))
		{
			gc_free(data->mem_ps, line);
			line = gc_get_next_line(data->mem_ps, fd);
			continue ;
		}
		parse_config_line(data, &line);
		line = gc_get_next_line(data->mem_ps, fd);
	}
	gc_free_all_mem(data->mem_ps);
	close(fd);
}

void	parse_config_line(t_data_ms *data, char **line)
{
	t_ast_main	*ast;

	if ((*line)[ft_strlen(*line) - 1] == '\n')
		(*line)[ft_strlen(*line) - 1] = '\0';
	if ((*line)[0] == '#')
		return ;
	if (*line == NULL || (int)ft_strlen((*line)) < 0)
		return ;
	check_error(data, line);
	if (*line == NULL)
		return ;
	ast = lexer(data, *line);
	if (ast)
		exec(data, &ast);
}

int	create_config_file(void)
{
	int		fd;

	fd = open(".msh_config", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);
	write(fd, "# minishell config file\n", 24);
	write(fd, "\n# prompt\n", 10);
	write(fd, "export PS1='\\[\\033[1;32m\\]\\u@minishell\\[\\033[0;00m", 50);
	write(fd, "\\]:\\[\\033[1;34m\\]\\w\\[\\033[0;00m\\]$ '", 36);
	write(fd, "\n# aliases\n", 11);
	write(fd, "alias ls='ls --color=auto'\n", 27);
	write(fd, "alias ll='ls -alF'\n", 19);
	write(fd, "alias la='ls -A'\n", 17);
	write(fd, "alias l='ls -CF'\n", 17);
	write(fd, "alias grep='grep --color=auto'\n", 31);
	write(fd, "alias ..='cd ..'\n", 17);
	write(fd, "alias ...='cd ../..'\n", 21);
	write(fd, "alias df='df -h'\n", 17);
	write(fd, "alias du='du -h'\n", 17);
	close (fd);
	fd = open(".msh_config", O_RDWR | O_CREAT | O_APPEND, 0666);
	return (fd);
}
