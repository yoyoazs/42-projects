/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 12:07:30 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/02 11:06:15 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_is_sorted(t_stack_number *stack)
{
	t_stack_number	*tmp;

	tmp = stack;
	while (tmp->next)
	{
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	stack;
	char	**tab;

	if (argc <= 1)
		return (0);
	tab = handle_args(argv);
	ft_bzero(&stack, sizeof(t_stack));
	stack.b = NULL;
	stack.a = init_stack(&stack, &tab);
	update_stack_info(&stack);
	set_index(stack.a, stack.a_info.size, stack.a_info.min);
	sort(&stack);
	show_all_moves(&stack);
	free_stack(&stack);
	exit(EXIT_SUCCESS);
}
