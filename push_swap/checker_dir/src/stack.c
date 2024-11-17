/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 01:26:31 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 12:24:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

t_stack_number	*init_stack(t_stack *stack, char ***tab)
{
	t_stack_number	*stack_numbered;
	int				i;

	i = -1;
	stack->b = NULL;
	stack_numbered = NULL;
	while ((*tab)[++i])
	{
		if (i == 0)
			stack_numbered = new_stack_number(ft_atoi((*tab)[i]), i);
		else
			add_stack_back(&stack_numbered,
				new_stack_number(ft_atoi((*tab)[i]), i));
	}
	return (stack_numbered);
}
