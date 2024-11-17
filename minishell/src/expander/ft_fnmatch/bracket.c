/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:57:23 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/08 08:41:10 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_check_bracket(int *k, int *neg, int *l)
{
	*k = 0;
	*neg = 0;
	*l = 0;
}

int	check_bracket(t_fnmatch *fm, int p, int i, const char *str)
{
	int	j;
	int	k;
	int	neg;
	int	l;

	j = p + 1;
	init_check_bracket(&k, &neg, &l);
	if (fm->p_pattern[j] == '!' || fm->p_pattern[j] == '^')
	{
		neg = 1;
		j++;
	}
	while (fm->p_pattern[j] && fm->p_pattern[j] != ']')
	{
		if (fm->p_pattern[j] == '-')
			l = (int)fm->p_pattern[j - 1];
		else if (fm->p_pattern[j] == str[fm->s + i]
			|| (l && l <= str[fm->s + i] && str[fm->s + i] <= fm->p_pattern[j]))
			k = 1;
		j++;
	}
	if ((k == 0 && neg == 0) || (k == 1 && neg == 1))
		return (0);
	return (j + 1);
}
