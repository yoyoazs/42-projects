/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:58:29 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/05/24 09:20:38 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Allocate memory with the garbage collector.
 * If use_calloc is true, allocate memory with ft_calloc, otherwise use malloc.
 * Adds the allocated block to the hash table.
 * 
 * @param size The total size of memory to allocate.
 * @param use_calloc Flag indicating whether to use calloc or malloc for
 * allocation.
 * @return A pointer to the allocated memory.
 */
static inline void	*gc_allocate(t_memory_table *memory_table, size_t size)
{
	void			*ptr;
	uint32_t		index;
	t_memory_block	*new_block;

	if (!memory_table || !memory_table->table)
		gc_error(memory_table, "No memory table");
	new_block = malloc(size + sizeof(t_memory_block));
	if (!new_block)
		gc_error(memory_table, "Allocation error");
	ptr = (void *)(new_block + 1);
	new_block->ptr = ptr;
	new_block->free_fun = NULL;
	new_block->next = NULL;
	index = hash(memory_table, ptr);
	new_block->next = memory_table->table[index];
	memory_table->table[index] = new_block;
	return (ptr);
}

/**
 * Allocate memory with the garbage collector using malloc.
 * 
 * @param size The size of memory to allocate.
 * @return A pointer to the allocated memory.
 */
void	*gc_malloc(t_memory_table *memory_table, size_t size)
{
	return (gc_allocate(memory_table, size));
}

/**
 * Allocate memory with the garbage collector using calloc.
 * 
 * @param n Number of elements to allocate.
 * @param size Size of each element.
 * @return A pointer to the allocated memory.
 */
void	*gc_calloc(t_memory_table *memory_table, size_t n, size_t size)
{
	return (gc_allocate(memory_table, n * size));
}
