/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:57:54 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/09 09:57:35 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

void	minishell_check(t_data_ms *data, char **line)
{
	if (ft_strlen(*line) > 0 && !(ft_strlen(*line) == 1 && (*line)[0] == ' '))
	{
		if (g_signal != 0)
		{
			data->cmd = g_signal;
			g_signal = 0;
		}
		use_line(data, line);
	}
}

static void	minishell(t_data_ms *data)
{
	char	*line;
	char	*prompt;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
		return (handle_non_interactive_mode());
	while (1)
	{
		prompt = get_prompt(data);
		line = readline(prompt, data->env, data->mem, false);
		if (line == NULL)
			break ;
		if (is_empty(line))
		{
			gc_free(data->mem, line);
			continue ;
		}
		minishell_check(data, &line);
		gc_free(data->mem, line);
		gc_free(data->mem, prompt);
	}
	save_historic();
	rl_clear_history();
	write(2, "\nexit\n", 6);
	gc_exit(data->cmd);
}

static void	alloc_env(t_data_ms *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->env = gc_calloc(data->mem, sizeof(char *), i + 1);
	i = 0;
	while (env[i])
	{
		data->env[i] = gc_strdup(data->mem, env[i]);
		i++;
	}
	data->env[i] = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data_ms	data;

	data.mem = gc_init();
	alloc_env(&data, env);
	data.alias = NULL;
	data.std = NULL;
	data.cmd = 0;
	signal_type();
	init_shell(&data);
	minishell(&data);
	(void)argc;
	(void)argv;
}
