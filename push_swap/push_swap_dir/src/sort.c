/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:51:36 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/27 16:44:25 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_stack *stack)
{
	if (stack->a->value == stack->a_info.min)
	{
		sa(stack, 0);
		ra(stack, 0);
	}
	else if (stack->a->value == stack->a_info.max)
	{
		if (stack->a->next->value == stack->a_info.min)
			ra(stack, 0);
		else
		{
			sa(stack, 0);
			rra(stack, 0);
		}
	}
	else
	{
		if (stack->a->next->value == stack->a_info.min)
			sa(stack, 0);
		else
			rra(stack, 0);
	}
}

void	push_all_but_3(t_stack *stack)
{
	int	pos;

	while (stack->a_info.size != 3)
	{
		update_stack_info_by_stack(stack->a, &stack->a_info);
		pos = get_pos(stack, stack->a_info.min);
		if (pos < stack->a_info.size / 2)
			while (--pos > -1)
				ra(stack, 0);
		else
			while (++pos < stack->a_info.size + 1)
				rra(stack, 0);
		pb(stack, 0);
	}
}

void	sort_5(t_stack *stack)
{
	push_all_but_3(stack);
	update_stack_info(stack);
	if (!stack_is_sorted(stack->a))
		sort_3(stack);
	if (stack->b_info.size == 2 && stack_is_sorted(stack->b))
		rb(stack, 0);
	while (stack->b)
		pa(stack, 0);
}

void	sort_n(t_stack *stack, int size_chunk)
{
	int	i;

	i = -1;
	while (++i < NUMBER_ATTEMPTS)
	{
		update_stack_info(stack);
		move_all_by_chunk(stack, size_chunk, i);
		sort_chunk(stack, i);
		reset_stack(stack);
		size_chunk++;
	}
}

void	sort(t_stack *stack)
{
	if (stack_is_sorted(stack->a))
		return ;
	update_stack_info(stack);
	if (stack->a_info.size == 2)
		sa(stack, 0);
	else if (stack->a_info.size == 3)
		sort_3(stack);
	else if (stack->a_info.size <= 5)
		sort_5(stack);
	else if (stack->a_info.size <= 120)
		sort_n(stack, SIZE_CHUNK_120);
	else
		sort_n(stack, SIZE_CHUNK_N);
}
