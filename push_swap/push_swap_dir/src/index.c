/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:24:26 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/07 03:29:24 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_index_max(t_stack *stack)
{
	t_stack_number	*tmp;
	int				max;

	tmp = stack->b;
	max = 0;
	while (tmp)
	{
		if (tmp->index > max)
			max = tmp->index;
		tmp = tmp->next;
	}
	return (max);
}

int	get_index_before_max(t_stack *stack)
{
	t_stack_number	*tmp;
	int				before_max;
	const int		max = get_index_max(stack);

	tmp = stack->b;
	before_max = 0;
	while (tmp)
	{
		if (tmp->index > before_max && tmp->index != max)
			before_max = tmp->index;
		tmp = tmp->next;
	}
	return (before_max);
}

int	get_pos_index(t_stack *stack, int index)
{
	t_stack_number	*tmp;

	tmp = stack->b;
	while (tmp)
	{
		if (tmp->index == index)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}

void	set_index(t_stack_number *stack, int size, int min)
{
	t_stack_number	*tmp;
	t_stack_number	*high;
	int				value;

	while (size-- > 0)
	{
		tmp = stack;
		value = min;
		high = NULL;
		while (tmp)
		{
			if (tmp->value == min && tmp->index == -1)
				tmp->index = 1;
			if (tmp->value > value && tmp->index == -1)
			{
				value = tmp->value;
				high = tmp;
				tmp = stack;
			}
			else
				tmp = tmp->next;
		}
		if (high != NULL)
			high->index = size;
	}
}
