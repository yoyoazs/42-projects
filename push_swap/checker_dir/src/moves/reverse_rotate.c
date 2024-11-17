/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:51:51 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 11:57:54 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

int	rra(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		reverse_rotate(&stack->a);
	return (1);
}

int	rrb(t_stack *stack)
{
	if (stack->b && stack->b->next != NULL)
		reverse_rotate(&stack->b);
	return (1);
}

int	rrr(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		reverse_rotate(&stack->a);
	if (stack->b && stack->b->next != NULL)
		reverse_rotate(&stack->b);
	return (1);
}
