/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:45:42 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 22:17:29 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*hostname_loop(t_data_ms *data, char **hostname)
{
	int		i;
	char	*tmp;

	i = -1;
	while ((*hostname)[++i])
	{
		if ((*hostname)[i] == '.')
		{
			tmp = gc_strndup(data->mem, *hostname, i);
			gc_free(data->mem, *hostname);
			return (tmp);
		}
	}
	return (*hostname);
}

char	*get_hostname(t_data_ms *data,	int full)
{
	char	*hostname;
	char	*tmp;
	int		fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (gc_strdup(data->mem, "unknown"));
	tmp = get_next_line(fd);
	hostname = gc_strndup(data->mem, tmp, ft_strlen(tmp) - 1);
	free(tmp);
	if (hostname == NULL)
		return (gc_strdup(data->mem, "unknown"));
	close(fd);
	if (full)
		return (hostname);
	return (hostname_loop(data, &hostname));
}

char	*get_username(t_data_ms *data)
{
	char	*username;

	username = get_env_var(data->mem, data->env, "USER");
	if (!username)
		return (gc_strdup(data->mem, "unknown"));
	return (username);
}

void	get_prompt_data(char *prompt, t_data_ms *data, int i, char **tmp)
{
	if (prompt[i] == '\\')
	{
		if (prompt[i + 1] == 'H')
			*tmp = get_hostname(data, 1);
		else if (prompt[i + 1] == 'h')
			*tmp = get_hostname(data, 0);
		else if (prompt[i + 1] == 'w')
			*tmp = get_cwd(data, 0);
		else if (prompt[i + 1] == 'W')
			*tmp = get_cwd(data, 1);
		else if (prompt[i + 1] == '\\')
			*tmp = gc_strdup(data->mem, "\\");
		else if (prompt[i + 1] == 'u')
			*tmp = get_username(data);
		else if (prompt[i + 1] == '[')
			*tmp = gc_strdup(data->mem, "\001");
		else if (prompt[i + 1] == ']')
			*tmp = gc_strdup(data->mem, "\002");
	}
}

char	*get_prompt(t_data_ms *data)
{
	char	*prompt;
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = NULL;
	i = -1;
	prompt = transform_to_ansii(data, get_env_var(data->mem, data->env, "PS1"));
	if (!prompt)
		return (gc_strdup(data->mem, "minishell$ "));
	while (prompt[++i])
	{
		get_prompt_data(prompt, data, i, &tmp);
		if (tmp)
		{
			tmp2 = gc_strndup(data->mem, prompt, i);
			tmp2 = gc_strjoin(data->mem, tmp2, tmp);
			tmp2 = gc_strjoin(data->mem, tmp2, prompt + i + 2);
			gc_free(data->mem, tmp);
			gc_free(data->mem, prompt);
			prompt = tmp2;
			tmp = NULL;
		}
	}
	return (prompt);
}
