/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:44:13 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/04 18:10:26 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define SIZE_CHUNK_120 11
# define SIZE_CHUNK_N 37
# define NUMBER_ATTEMPTS 30

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

typedef struct s_move {
	char			*move;
	struct s_move	*next;
}	t_move;

typedef struct s_move_info {
	int		number;
	t_move	*moves;
}	t_move_info;

typedef struct s_stack_info {
	int				min;
	int				max;
	int				size;
}	t_stack_info;

typedef struct s_stack {
	t_stack_number	*a;
	t_stack_number	*b;
	t_stack_info	a_info;
	t_stack_info	b_info;
	t_move_info		*move_info[NUMBER_ATTEMPTS];
	char			**init_tab;
}	t_stack;

char			**handle_args(char **argv);

void			pa(t_stack *stack, int attempts);
void			pb(t_stack *stack, int attempts);
void			sa(t_stack *stack, int attempts);
void			sb(t_stack *stack, int attempts);
void			ss(t_stack *stack, int attempts);
void			ra(t_stack *stack, int attempts);
void			rb(t_stack *stack, int attempts);
void			rr(t_stack *stack, int attempts);
void			rra(t_stack *stack, int attempts);
void			rrb(t_stack *stack, int attempts);
void			rrr(t_stack *stack, int attempts);

void			sort_chunk(t_stack *stack, int attempts);
void			move_all_by_chunk(t_stack *stack, int size_chunk, int attempts);
int				stack_is_sorted(t_stack_number *stack);
void			sort(t_stack *stack);

void			set_index(t_stack_number *stack, int size, int min);
int				get_pos_index(t_stack *stack, int index);
int				get_index_max(t_stack *stack);
int				get_index_before_max(t_stack *stack);

t_move			*add_move_back(t_move_info **move_info, t_move **move,
					t_move *new);
t_move			*new_move(char *move);

void			show_all_moves(t_stack *stack);
int				get_pos_closer(t_stack *stack, int min, int max, char name);
int				get_pos(t_stack *stack, int value);

t_stack_number	*init_stack(t_stack *stack, char ***argc);
void			reset_stack(t_stack *stack);
t_stack_number	*add_stack_front(t_stack_number **stack, t_stack_number *new);

void			update_stack_info(t_stack *stack);
void			update_stack_info_by_stack(t_stack_number *stack,
					t_stack_info *info);
t_stack_number	*get_last(t_stack_number *stack);
t_stack_number	*get_stack_before_last(t_stack_number *stack);

void			free_stack(t_stack *stack);
char			**free_tab(char **tab);
void			exit_error(t_stack *stack);

#endif