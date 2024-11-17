/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:33:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/07 03:45:52 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_number	*get_last(t_stack_number *stack)
{
	t_stack_number	*tmp;

	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack_number	*get_stack_before_last(t_stack_number *stack)
{
	t_stack_number	*tmp;

	tmp = stack;
	while (tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}

void	update_stack_info_by_stack(t_stack_number *stack, t_stack_info *info)
{
	t_stack_number	*tmp;
	int				i;

	i = 0;
	info->size = 0;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value < info->min || i == 0)
			info->min = tmp->value;
		if (tmp->value > info->max || i == 0)
			info->max = tmp->value;
		info->size++;
		tmp->pos = i++;
		tmp = tmp->next;
	}
}

void	update_stack_info(t_stack *stack)
{
	update_stack_info_by_stack(stack->a, &stack->a_info);
	update_stack_info_by_stack(stack->b, &stack->b_info);
}
