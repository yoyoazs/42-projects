/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:25:15 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/27 15:27:28 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_pos(t_stack *stack, int value)
{
	t_stack_number	*tmp;

	tmp = stack->a;
	while (tmp)
	{
		if (tmp->value == value)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}

int	get_pos_closer(t_stack *stack, int min, int max, char name)
{
	t_stack_number	*tmp;

	if (name == 'a')
		tmp = stack->a;
	else
		tmp = stack->b;
	while (tmp)
	{
		if (tmp->index >= min && tmp->index <= max)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}

int	get_best_attempts(t_stack stack)
{
	int	i;
	int	best_attempts;
	int	best_number;

	i = -1;
	best_attempts = 0;
	best_number = 0;
	while (++i < NUMBER_ATTEMPTS)
	{
		if (best_number == 0 || (best_number > stack.move_info[i]->number
				&& stack.move_info[i]->number != 0))
		{
			best_number = stack.move_info[i]->number;
			best_attempts = i;
		}
	}
	return (best_attempts);
}

void	show_all_moves(t_stack *stack)
{
	t_move	*tmp;
	int		best_attempts;

	best_attempts = get_best_attempts(*stack);
	tmp = stack->move_info[best_attempts]->moves;
	while (tmp)
	{
		ft_printf("%s\n", tmp->move);
		tmp = tmp->next;
	}
}
