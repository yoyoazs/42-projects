/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:29:47 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 12:42:57 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	exec_op(t_stack *stack, char *op)
{
	if (ft_strncmp(op, "sa", 2) == 0)
		return (sa(stack));
	else if (ft_strncmp(op, "sb", 2) == 0)
		return (sb(stack));
	else if (ft_strncmp(op, "ss", 2) == 0)
		return (ss(stack));
	else if (ft_strncmp(op, "rra", 3) == 0)
		return (rra(stack));
	else if (ft_strncmp(op, "rrb", 3) == 0)
		return (rrb(stack));
	else if (ft_strncmp(op, "rrr", 3) == 0)
		return (rrr(stack));
	else if (ft_strncmp(op, "ra", 2) == 0)
		return (ra(stack));
	else if (ft_strncmp(op, "rb", 2) == 0)
		return (rb(stack));
	else if (ft_strncmp(op, "rr", 2) == 0)
		return (rr(stack));
	else if (ft_strncmp(op, "pa", 2) == 0)
		return (pa(stack));
	else if (ft_strncmp(op, "pb", 2) == 0)
		return (pb(stack));
	return (0);
}

void	check_is_sorted(t_stack *stack)
{
	t_stack_number	*tmp_a;
	t_stack_number	*tmp_b;

	tmp_a = stack->a;
	tmp_b = stack->b;
	if (tmp_b)
	{
		ft_printf("KO\n");
		return ;
	}
	while (tmp_a->next)
	{
		if (tmp_a->value > tmp_a->next->value)
		{
			ft_printf("KO\n");
			return ;
		}
		tmp_a = tmp_a->next;
	}
	ft_printf("OK\n");
}

int	main(int argc, char **argv)
{
	t_stack	stack;
	char	**tab;
	char	*str;
	int		error;

	error = 0;
	if (argc <= 1)
		return (0);
	tab = handle_args(argv);
	ft_bzero(&stack, sizeof(t_stack));
	stack.a = init_stack(&stack, &tab);
	free_tab(tab);
	str = get_next_line(0);
	while (str)
	{
		if (!exec_op(&stack, str))
			error = 1;
		free(str);
		str = get_next_line(0);
	}
	if (error)
		exit_error(&stack);
	check_is_sorted(&stack);
	free_stack(&stack);
	free(str);
}
