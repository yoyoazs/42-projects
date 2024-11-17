/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 15:21:14 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 11:57:39 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	push(t_stack_number **tab_a, t_stack_number **tab_b)
{
	t_stack_number	*tmp;

	if (*tab_a == NULL)
		return ;
	tmp = (*tab_a)->next;
	*tab_a = add_stack_front(tab_b, *tab_a);
	*tab_a = tmp;
}

int	pa(t_stack *stack)
{
	if (stack->b != NULL)
		push(&stack->b, &stack->a);
	return (1);
}

int	pb(t_stack *stack)
{
	if (stack->a != NULL)
		push(&stack->a, &stack->b);
	return (1);
}
