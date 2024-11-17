/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 03:45:35 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/12 10:17:32 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_attempts(t_stack *stack)
{
	int		i;
	t_move	*tmp;

	i = -1;
	while (++i < NUMBER_ATTEMPTS)
	{
		while (stack->move_info[i]->moves)
		{
			tmp = stack->move_info[i]->moves;
			stack->move_info[i]->moves = stack->move_info[i]->moves->next;
			free(tmp);
		}
		free(stack->move_info[i]);
	}
}

char	**free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

void	free_stack(t_stack *stack)
{
	t_stack_number	*tmp;

	while (stack->a)
	{
		tmp = stack->a;
		stack->a = stack->a->next;
		free(tmp);
	}
	while (stack->b)
	{
		tmp = stack->b;
		stack->b = stack->b->next;
		free(tmp);
	}
	free_attempts(stack);
	free_tab(stack->init_tab);
}

void	exit_error(t_stack *stack)
{
	if (stack)
		free_stack(stack);
	ft_putendl_fd("Error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
