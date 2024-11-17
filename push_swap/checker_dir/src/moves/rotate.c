/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:19:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 12:06:56 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

int	ra(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		rotate(&stack->a);
	return (1);
}

int	rb(t_stack *stack)
{
	if (stack->b && stack->b != NULL && stack->b->next != NULL)
		rotate(&stack->b);
	return (1);
}

int	rr(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		rotate(&stack->a);
	if (stack->a && stack->b->next != NULL)
		rotate(&stack->b);
	return (1);
}
