/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:19:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/07 03:17:37 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_stack_number **stack)
{
	t_stack_number	*tmp;
	t_stack_number	*last;

	tmp = *stack;
	*stack = (*stack)->next;
	last = get_last(*stack);
	tmp->next = NULL;
	last->next = tmp;
}

void	ra(t_stack *stack, int attempts)
{
	if (stack->a_info.size >= 1)
	{
		rotate(&stack->a);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("ra"));
	}
}

void	rb(t_stack *stack, int attempts)
{
	if (stack->b_info.size >= 1)
	{
		rotate(&stack->b);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("rb"));
	}
}

void	rr(t_stack *stack, int attempts)
{
	if (stack->a_info.size >= 1)
		rotate(&stack->a);
	if (stack->b_info.size >= 1)
		rotate(&stack->b);
	add_move_back(&stack->move_info[attempts],
		&stack->move_info[attempts]->moves, new_move("rr"));
}
