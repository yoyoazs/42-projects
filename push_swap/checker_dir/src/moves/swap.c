/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:06:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 12:20:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_stack_number **a)
{
	int	tmp;

	if ((*a) == NULL || (*a)->next == NULL)
		return ;
	tmp = (*a)->value;
	(*a)->value = (*a)->next->value;
	(*a)->next->value = tmp;
	tmp = (*a)->index;
	(*a)->index = (*a)->next->index;
	(*a)->next->index = tmp;
}

int	sa(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		swap(&stack->a);
	return (1);
}

int	sb(t_stack *stack)
{
	if (stack->b && stack->b->next != NULL)
		swap(&stack->b);
	return (1);
}

int	ss(t_stack *stack)
{
	if (stack->a && stack->a->next != NULL)
		swap(&stack->a);
	if (stack->b && stack->b->next != NULL)
		swap(&stack->b);
	return (1);
}
