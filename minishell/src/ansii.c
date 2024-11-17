/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ansii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:56:49 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 08:30:11 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	transform_to_ansii_loop_2(char *str, int *i, int *j, char **ansii)
{
	if (str[*i] == 'n')
		(*ansii)[*j] = '\n';
	else if (str[*i] == 'e')
		(*ansii)[*j] = '\e';
	else if (str[*i] == '0' && str[*i + 1] == 'x' && str[*i + 2] == '1'
		&& str[*i + 3] == 'B')
	{
		*i += 4;
		(*ansii)[*j] = '\033';
	}
	else if (str[*i] == '0' && str[*i + 1] == '3' && str[*i + 2] == '3')
	{
		*i += 2;
		(*ansii)[*j] = '\033';
	}
	else if (str[*i] == '0')
		(*ansii)[*j] = '\0';
	else
	{
		(*ansii)[*j] = '\\';
		(*j)++;
		(*ansii)[*j] = str[*i];
	}
}

static void	transform_to_ansii_loop(char *str, int *i, int *j, char **ansii)
{
	if (str[*i] == '\\' && str[*i + 1])
	{
		(*i)++;
		if (str[*i] == 'a')
			(*ansii)[*j] = '\a';
		else if (str[*i] == 'b')
			(*ansii)[*j] = '\b';
		else if (str[*i] == 't')
			(*ansii)[*j] = '\t';
		else if (str[*i] == 'r')
			(*ansii)[*j] = '\r';
		else if (str[*i] == 'v')
			(*ansii)[*j] = '\v';
		else if (str[*i] == 'f')
			(*ansii)[*j] = '\f';
		else
			transform_to_ansii_loop_2(str, i, j, ansii);
	}
	else
		(*ansii)[*j] = str[*i];
}

char	*transform_to_ansii(t_data_ms *data, char *str)
{
	char	*ansii;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	ansii = gc_malloc(data->mem, ft_strlen(str) + 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		transform_to_ansii_loop(str, &i, &j, &ansii);
		j++;
	}
	ansii[j] = '\0';
	gc_free(data->mem, str);
	return (ansii);
}
