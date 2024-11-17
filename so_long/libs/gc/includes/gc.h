/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 17:23:08 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:52:50 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include "libft.h"
# include <stdint.h>

# define MEMORY_TABLE_SIZE 1024

typedef struct s_block_info
{
	void	*ptr;
	void	*ptr2;
}	t_block_info;

typedef struct s_memory_block {
	void					*ptr;
	void					*free_fun;
	t_block_info			*info;
	struct s_memory_block	*next;
}	t_memory_block;

typedef struct s_memory_table {
	size_t			size;
	t_memory_block	**table;
}	t_memory_table;

t_memory_table	*gc_init(void);
void			*gc_malloc(t_memory_table *memory_table, size_t size);
void			*gc_calloc(t_memory_table *memory_table, size_t n, size_t size);
void			*gc_strdup(t_memory_table *memory_table, char *s);
void			*gc_strjoin(t_memory_table *memory_table, char *s1, char *s2);
void			gc_exit(t_memory_table *memory_table);
void			gc_free(t_memory_table *memory_table, void *ptr);
uint32_t		hash(t_memory_table *memory_table, void *ptr);
void			gc_error(t_memory_table *memory_table, char *msg);
void			gc_add_memory_block(t_memory_table *memory_table, void *ptr,
					void (*free_func)(t_block_info *), t_block_info *info);

#endif