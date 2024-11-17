/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 09:58:19 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/09 09:58:55 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "minishell.h"

#define MAX_LINE_LENGTH 1024

void	delete_hd_file(t_cmd *cmd)
{
	t_std	*current;

	current = (*cmd->std);
	while (current)
	{
		if (current->lim && current->lim_crafted == true)
		{
			if (cmd->int_in > 0)
				close(cmd->int_in);
			unlink(current->name);
		}
		current = current->next;
	}
}

void	dollard(t_cmd *cmd, char **env, char **line)
{
	size_t			i;
	t_mem_and_cmd	*info;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			info = set_mem_info(cmd->mem, cmd->ret);
			handle_dollar(info, env, line, &i);
			gc_free(cmd->mem, info);
		}
	}
}

int	crafting_doc(int fd, char *eof, t_cmd *cmd, char ***env)
{
	char	*line;

	while (1)
	{
		line = readline(">", *env, cmd->mem, false);
		if (!line)
		{
			hd_ctrld_msg(eof, cmd);
			break ;
		}
		if (line[0] == '\n')
			return (gc_free(cmd->mem, line), cmd->pb = 130);
		if ((!ft_strncmp(line, eof, ft_strlen(eof)) \
			&& ft_strlen(eof) == ft_strlen(line)))
			break ;
		if (cmd->expand)
			dollard(cmd, *env, &line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		gc_free(cmd->mem, line);
	}
	if (line)
		gc_free(cmd->mem, line);
	return (1);
}

void	create_msh_file(t_std *c, int iter, t_cmd *cmd)
{
	char	*to_del;
	char	*rand;
	char	*tiret;

	to_del = ft_itoa(c->number);
	rand = ft_itoa(ft_rand(1000000, 9999999));
	tiret = gc_strdup(cmd->mem, "_");
	c->name = gc_strjoin(cmd->mem, gc_strdup(cmd->mem, ".msh_"), to_del);
	c->name = gc_strjoin(cmd->mem, c->name, tiret);
	c->name = gc_strjoin(cmd->mem, c->name, rand);
	free(rand);
	free(to_del);
	gc_free(cmd->mem, tiret);
	iter++;
	if (!access(c->name, F_OK) && access(c->name, W_OK | R_OK))
	{
		gc_free(cmd->mem, c->name);
		if (iter > 100)
		{
			ft_putstr_fd("fail to create here_doc\n", 2);
			cmd->pb = 1;
			return ;
		}
		create_msh_file(c, iter, cmd);
	}
}

void	crossing_craft_doc(t_cmd *cmd, char ***env)
{
	t_std				*current;
	int					fd;
	char				*tmp;

	current = (*cmd->std);
	while (current)
	{
		if (current->lim)
		{
			tmp = gc_strdup(cmd->mem, current->name);
			create_msh_file(current, 0, cmd);
			if (cmd->pb == 1)
				return ;
			current->lim_crafted = true;
			fd = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			cmd->expand = current->expand;
			crafting_doc(fd, tmp, cmd, env);
			close(fd);
			gc_free(cmd->mem, tmp);
			if (cmd->pb == 130)
				break ;
		}
		current = current->next;
	}
}
