/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:21:14 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/07 15:27:41 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_stack_number **tab_a, t_stack_number **tab_b)
{
	t_stack_number	*tmp;

	if (*tab_a == NULL)
		return ;
	tmp = (*tab_a)->next;
	*tab_a = add_stack_front(tab_b, *tab_a);
	*tab_a = tmp;
}

void	pa(t_stack *stack, int attempts)
{
	if (stack->b_info.size > 0)
	{
		push(&stack->b, &stack->a);
		stack->a_info.size++;
		stack->b_info.size--;
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("pa"));
	}
}

void	pb(t_stack *stack, int attempts)
{
	if (stack->a_info.size > 0)
	{
		push(&stack->a, &stack->b);
		stack->a_info.size--;
		stack->b_info.size++;
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("pb"));
	}
}
