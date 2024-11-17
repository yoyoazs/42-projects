/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:30:39 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/08 12:13:12 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_move	*new_move(char *move)
{
	t_move	*new;

	new = (t_move *)malloc(sizeof(t_move));
	if (!new)
		return (NULL);
	new->move = move;
	new->next = NULL;
	return (new);
}

t_move	*get_last_move(t_move *move)
{
	t_move	*tmp;

	tmp = move;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	check_move(t_move **move, t_move **new)
{
	t_move	*tmp;
	int		replace;

	replace = 0;
	tmp = get_last_move(*move);
	if (ft_strncmp(tmp->move, "ra", 2) == 0
		&& ft_strncmp((*new)->move, "rb", 2) == 0)
		replace = 1;
	else if (ft_strncmp(tmp->move, "rb", 2) == 0
		&& ft_strncmp((*new)->move, "ra", 2) == 0)
		replace = 1;
	else if (ft_strncmp(tmp->move, "rra", 3) == 0
		&& ft_strncmp((*new)->move, "rrb", 3) == 0)
		replace = 2;
	else if (ft_strncmp(tmp->move, "rrb", 3) == 0
		&& ft_strncmp((*new)->move, "rra", 3) == 0)
		replace = 2;
	if (replace == 0)
		return (0);
	else if (replace == 1)
		tmp->move = "rr";
	else if (replace == 2)
		tmp->move = "rrr";
	return (1);
}

t_move	*add_move_back(t_move_info **move_info, t_move **move, t_move *new)
{
	t_move	*tmp;

	if (!new)
		return (NULL);
	if (!(*move))
	{
		*move = new;
		(*move_info)->number++;
	}
	else
	{
		if (!check_move(move, &new))
		{
			tmp = get_last_move(*move);
			tmp->next = new;
			(*move_info)->number++;
		}
		else
			free(new);
	}
	return (get_last_move(*move));
}
