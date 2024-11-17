/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:26:31 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/09 13:58:21 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_number	*new_stack_number(int num, int pos)
{
	t_stack_number	*new;

	new = (t_stack_number *)malloc(sizeof(t_stack_number));
	if (!new)
		return (NULL);
	new->value = num;
	new->index = -1;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

t_stack_number	*add_stack_back(t_stack_number **stack, t_stack_number *new)
{
	t_stack_number	*tmp;

	if (!*stack)
		*stack = new;
	else
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (new);
}

t_stack_number	*add_stack_front(t_stack_number **stack, t_stack_number *new)
{
	t_stack_number	*tmp;

	if (!*stack)
	{
		*stack = new;
		new->next = NULL;
	}
	else
	{
		tmp = *stack;
		*stack = new;
		new->next = tmp;
	}
	return (new);
}

void	reset_stack(t_stack *stack)
{
	t_stack_number	*tmp;
	int				i;

	i = 0;
	while (stack->a)
	{
		tmp = stack->a;
		stack->a = stack->a->next;
		free(tmp);
	}
	stack->a = NULL;
	while (++i <= stack->a_info.size)
	{
		if (i == 1)
			stack->a = new_stack_number(ft_atoi(stack->init_tab[i - 1]), i);
		else
			add_stack_back(&stack->a,
				new_stack_number(ft_atoi(stack->init_tab[i - 1]), i));
	}
	update_stack_info(stack);
	set_index(stack->a, stack->a_info.size, stack->a_info.min);
}

t_stack_number	*init_stack(t_stack *stack, char ***tab)
{
	t_stack_number	*stack_numbered;
	int				i;

	i = -1;
	stack_numbered = NULL;
	stack->init_tab = (*tab);
	while ((*tab)[++i])
	{
		if (i == 0)
			stack_numbered = new_stack_number(ft_atoi((*tab)[i]), i);
		else
			add_stack_back(&stack_numbered,
				new_stack_number(ft_atoi((*tab)[i]), i));
	}
	stack->a_info.size = i + 1;
	i = -1;
	while (++i < NUMBER_ATTEMPTS)
	{
		stack->move_info[i] = (t_move_info *)malloc(sizeof(t_move_info));
		if (!stack->move_info[i])
			exit_error(stack);
		stack->move_info[i]->number = 0;
		stack->move_info[i]->moves = NULL;
	}
	return (stack_numbered);
}
