/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:33:37 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/08 15:01:27 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_stack_number	*get_last(t_stack_number *stack)
{
	t_stack_number	*tmp;

	tmp = stack;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_stack_number	*get_stack_before_last(t_stack_number *stack)
{
	t_stack_number	*tmp;

	tmp = stack;
	while (tmp->next->next)
		tmp = tmp->next;
	return (tmp);
}
