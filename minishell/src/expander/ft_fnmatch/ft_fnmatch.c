/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:56:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/20 09:02:07 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fn_get_len(const char *string, const char *p_pattern)
{
	int			i;
	int			j;
	int			escape;
	const int	len = ft_strlen(string);

	escape = 0;
	j = 0;
	i = 0;
	while (p_pattern[j + i])
	{
		escape = 0;
		if (p_pattern[j + i] == '\\')
		{
			escape = 1;
			i++;
		}
		if (p_pattern[j + i] == '[' && !escape)
		{
			while (p_pattern[j + i] && p_pattern[j + i] != ']')
				j++;
		}
		i++;
	}
	return (len - i);
}

static int	fnmatch_check(t_memory_table *mem, t_fnmatch *fm,
const char *pattern)
{
	if (fm->p_pattern)
		gc_free(mem, fm->p_pattern);
	fm->p_pattern = gc_strdup(mem, "");
	fm->escape = 0;
	if (pattern[fm->p] == '\\' && pattern[fm->p + 1] == '*')
	{
		fm->p++;
		fm->escape = 1;
	}
	while (!fm->escape && pattern[fm->p] && pattern[fm->p] == '*')
		fm->p++;
	while (pattern[fm->p] != '*' && pattern[fm->p])
	{
		if (pattern[fm->p] == '\\' && pattern[fm->p + 1] == '*')
			fm->p++;
		if (pattern[fm->p])
			fm->p_pattern = gc_strjoin_char(mem, fm->p_pattern, pattern[fm->p]);
		fm->p++;
	}
	return (fm->p_pattern == NULL || ft_strlen(fm->p_pattern) == 0);
}

static int	fnmatch_loop(t_memory_table *mem, t_fnmatch *fm, const char *string,
const char *pattern)
{
	while (string[fm->s])
	{
		if (fm->p - ft_strlen(fm->p_pattern) == 0)
		{
			if (check_part(fm, string))
				break ;
			gc_free(mem, fm->p_pattern);
			return (0);
		}
		else if (pattern[fm->p] == '\0')
		{
			if (last_part(fm, string))
			{
				gc_free(mem, fm->p_pattern);
				return (1);
			}
			gc_free(mem, fm->p_pattern);
			return (0);
		}
		if (check_part(fm, string))
			break ;
		fm->s++;
	}
	return (-1);
}

static void	set_fm(t_fnmatch *fm)
{
	fm->s = 0;
	fm->p = 0;
	fm->loop = 0;
	fm->escape = 0;
	fm->p_pattern = NULL;
}

int	ft_fnmatch(t_memory_table *mem, const char *pattern, const char *str)
{
	t_fnmatch	fm;

	set_fm(&fm);
	if (!pattern || !str)
		return (0);
	while (str[fm.s] && pattern[fm.p])
	{
		if (fnmatch_check(mem, &fm, pattern))
			break ;
		fm.loop = fnmatch_loop(mem, &fm, str, pattern);
		if (fm.loop == 1)
			return (1);
		else if (fm.loop == 0)
			return (0);
	}
	if (fm.p_pattern)
	{
		fm.p = fm.p - ft_strlen(fm.p_pattern);
		gc_free(mem, fm.p_pattern);
	}
	while (pattern[fm.p] == '*')
		fm.p++;
	if (pattern[fm.p] == 0 || (pattern[fm.p] == '*' && pattern[fm.p + 1] == 0))
		return (1);
	return (0);
}
