/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:06:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/08 13:27:41 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	sa(t_stack *stack, int attempts)
{
	if (stack->a_info.size > 1)
	{
		swap(&stack->a);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("sa"));
	}
}

void	sb(t_stack *stack, int attempts)
{
	if (stack->b_info.size > 1)
	{
		swap(&stack->b);
		add_move_back(&stack->move_info[attempts],
			&stack->move_info[attempts]->moves, new_move("sb"));
	}
}

void	ss(t_stack *stack, int attempts)
{
	if (stack->a_info.size > 1)
		swap(&stack->a);
	if (stack->b_info.size > 1)
		swap(&stack->b);
	add_move_back(&stack->move_info[attempts],
		&stack->move_info[attempts]->moves, new_move("ss"));
}
