/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:23:35 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/27 16:44:15 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_to_top(t_stack *stack, int pos, char name, int attempts)
{
	if (pos == 0 || pos == -1)
		return ;
	if (name == 'a')
	{
		if (pos < stack->a_info.size / 2)
			while (--pos > -1)
				ra(stack, attempts);
		else
			while (++pos < stack->a_info.size + 1)
				rra(stack, attempts);
	}
	else
	{
		if (pos < stack->b_info.size / 2)
			while (--pos > -1)
				rb(stack, attempts);
		else
			while (++pos < stack->b_info.size + 1)
				rrb(stack, attempts);
	}
}

int	get_med_chunk(t_stack *stack, int min, int max)
{
	t_stack_number	*tmp;
	int				med;
	int				i;

	tmp = stack->a;
	med = 0;
	i = 0;
	while (tmp)
	{
		if (tmp->index >= min && tmp->index <= max)
		{
			med += tmp->index;
			i++;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		return (0);
	return (med / i);
}

void	move_all_by_chunk(t_stack *stack, int size_chunk, int attempts)
{
	int	med;
	int	chunks;
	int	i;

	chunks = 0;
	while (stack->a)
	{
		update_stack_info(stack);
		med = get_med_chunk(stack, chunks * size_chunk + 1,
				(chunks + 1) * size_chunk);
		i = 0;
		while (stack->a && i++ < size_chunk)
		{
			update_stack_info(stack);
			move_to_top(stack, get_pos_closer(stack, chunks * size_chunk + 1,
					(chunks + 1) * size_chunk, 'a'), 'a', attempts);
			pb(stack, attempts);
			if (stack->b->index < med && stack->b_info.size > 1)
				rb(stack, attempts);
		}
		chunks++;
	}
}

void	move_and_push(t_stack *stack, int first, int second, int attempts)
{
	move_to_top(stack, first, 'b', attempts);
	pa(stack, attempts);
	update_stack_info(stack);
	move_to_top(stack, get_pos_index(stack, second), 'b', attempts);
	pa(stack, attempts);
}

void	sort_chunk(t_stack *stack, int attempts)
{
	int	pos_first;
	int	pos_second;
	int	pos_tmpfirst;
	int	pos_tmpsecond;

	while (stack->b)
	{
		update_stack_info(stack);
		pos_first = get_pos_index(stack, get_index_max(stack));
		pos_second = get_pos_index(stack, get_index_before_max(stack));
		pos_tmpfirst = pos_first;
		pos_tmpsecond = pos_second;
		if (pos_first > stack->b_info.size / 2)
			pos_tmpfirst = stack->b_info.size - pos_first;
		if (pos_second > stack->b_info.size / 2)
			pos_tmpsecond = stack->b_info.size - pos_second;
		if (pos_tmpfirst < pos_tmpsecond)
			move_and_push(stack, pos_first,
				get_index_before_max(stack), attempts);
		else
			move_and_push(stack, pos_second, get_index_max(stack), attempts);
		if (stack->a->value > stack->a->next->value)
			sa(stack, attempts);
	}
}
