/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 03:08:43 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/09/09 09:21:12 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_void_before(char *line, int i)
{
	int	j;

	j = -1;
	while (i + j > 0 && line[i + j] && line[i + j] == ' ')
		j--;
	if (i + j <= 0)
		return (true);
	return (false);
}

bool	is_in_command_list(const char *command, char **all_commands, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (ft_strcmp(command, all_commands[i]) == 0)
			return (true);
	}
	return (false);
}

int	get_max_length(char **strings, int count)
{
	int	max_length;
	int	i;
	int	length;

	max_length = 0;
	i = -1;
	while (++i < count)
	{
		length = ft_strlen(strings[i]);
		if (length > max_length)
			max_length = length;
	}
	return (max_length);
}

void	bubble_sort(char **strings, int count)
{
	int		i;
	int		j;
	char	*temp;
	int		swapped;

	i = -1;
	while (++i < count - 1)
	{
		swapped = 0;
		j = -1;
		while (++j < count - i - 1)
		{
			if (ft_strcmp(strings[j], strings[j + 1]) > 0)
			{
				temp = strings[j];
				strings[j] = strings[j + 1];
				strings[j + 1] = temp;
				swapped = 1;
			}
		}
		if (!swapped)
			break ;
	}
}

void	auto_completion(t_readline *rl)
{
	size_t		i;
	bool		first;

	first = false;
	i = rl->index;
	while (i > 0 && rl->input[i - 1] != ' ')
		i--;
	if (rl->input[i] == '.' || rl->input[i] == '/')
		complete_file(rl, i);
	else
	{
		if (is_void_before(rl->input, i))
			first = true;
		if (first && rl->index > 0 && rl->input[i] && rl->input[i] != ' ')
			complete_command(rl);
		else if (!first)
			complete_file(rl, i);
	}
	reset_ligne(rl);
}
