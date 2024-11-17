/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:57:11 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 22:15:34 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_check_part(t_fnmatch *fm, int *p)
{
	fm->escape = 0;
	if (fm->p_pattern[*p] == '\\' && (fm->p_pattern[*p + 1] == '?'
			|| fm->p_pattern[*p + 1] == '['))
	{
		fm->escape = 1;
		(*p)++;
	}
}

static void	add_p_s(int *p, int *s)
{
	(*s)++;
	(*p)++;
}

int	check_part(t_fnmatch *fm, const char *string)
{
	int	s;
	int	p;

	s = 0;
	p = 0;
	while (string[fm->s + s] && fm->p_pattern && fm->p_pattern[p])
	{
		init_check_part(fm, &p);
		if (fm->p_pattern[p] == '[' && !fm->escape)
		{
			p = check_bracket(fm, p, s, string);
			if (p == 0)
				return (0);
			s++;
		}
		else if ((fm->p_pattern[p] == '?' && !fm->escape)
			|| fm->p_pattern[p] == string[fm->s + s])
			add_p_s(&p, &s);
		else
			break ;
	}
	fm->s += s;
	return (fm->p_pattern[p] == '\0');
}

int	last_part(t_fnmatch *fm, const char *string)
{
	int	temp;

	temp = fm->s;
	fm->s = fn_get_len(string, fm->p_pattern);
	if (fm->s < temp)
		return (0);
	return (check_part(fm, string));
}
