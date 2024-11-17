/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:29:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 12:22:17 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# ifndef MIN_INT
#  define MIN_INT -2147483648
# endif

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

# include "../../libft/includes/libft.h"

typedef struct s_stack_number {
	int						value;
	int						index;
	int						pos;
	struct s_stack_number	*next;
}	t_stack_number;

typedef struct s_stack {
	t_stack_number	*a;
	t_stack_number	*b;
}	t_stack;

int				pa(t_stack *stack);
int				pb(t_stack *stack);
int				sa(t_stack *stack);
int				sb(t_stack *stack);
int				ss(t_stack *stack);
int				ra(t_stack *stack);
int				rb(t_stack *stack);
int				rr(t_stack *stack);
int				rra(t_stack *stack);
int				rrb(t_stack *stack);
int				rrr(t_stack *stack);

char			**handle_args(char **argv);
t_stack_number	*init_stack(t_stack *stack, char ***tab);
t_stack_number	*get_last(t_stack_number *stack);
t_stack_number	*get_stack_before_last(t_stack_number *stack);

t_stack_number	*add_stack_back(t_stack_number **stack, t_stack_number *new);
t_stack_number	*add_stack_front(t_stack_number **stack, t_stack_number *new);

void			exit_error(t_stack *stack);
void			free_stack(t_stack *stack);
char			**free_tab(char **tab);

#endif
