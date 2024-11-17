/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:51:51 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/07 03:17:06 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack_number **stack)
{
	t_stack_number	*tmp;
	t_stack_number	*last;
	t_stack_number	*before_last;

	last = get_last(*stack);
	before_last = get_stack_before_last(*stack);
	tmp = *stack;
	*stack = last;
	(*stack)->next = tmp;
	before_last->next = NULL;
}

void	rra(t_stack *stack, int attempts)
{
	if (stack->a_info.size > 0)
	{
		reverse_rotate(&stack->a);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("rra"));
	}
}

void	rrb(t_stack *stack, int attempts)
{
	if (stack->b_info.size > 0)
	{
		reverse_rotate(&stack->b);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("rrb"));
	}
}

void	rrr(t_stack *stack, int attempts)
{
	if (stack->a_info.size > 0)
		reverse_rotate(&stack->a);
	if (stack->b_info.size > 0)
		reverse_rotate(&stack->b);
	add_move_back(&stack->move_info[attempts],
		&stack->move_info[attempts]->moves, new_move("rrr"));
}
