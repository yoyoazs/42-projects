/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:40:38 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/01 10:32:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Frees a memory block.
 *
 * This function frees the memory block specified by the provided pointer.
 * If the block has an associated function, it is called with associated
 * arguments.
 * Otherwise, the memory pointed to by the block is deallocated using free().
 *
 * @param block Pointer to the memory block to be freed.
 */
static inline void	free_block(t_memory_block *block)
{
	if (block->free_fun)
		((void (*)(void *))block->free_fun)(block->ptr);
	free(block);
}

/**
 * Free all memory allocated by the garbage collector.
 * Iterates through the hash table and frees all memory blocks
 * contained in it.
 * 
 * @param memory_table The memory table to free.
 */
void	gc_free_all(t_memory_table *memory_table)
{
	register size_t	i;
	t_memory_block	*block;
	t_memory_block	*next_block;

	i = -1;
	while (memory_table && ++i < memory_table->size && memory_table->table)
	{
		block = memory_table->table[i];
		while (block != NULL)
		{
			next_block = block->next;
			if (block->free_fun)
				((void (*)(void *))block->free_fun)(block->info);
			free(block);
			block = next_block;
		}
	}
}

/**
 * Free all memory allocated by the garbage collector.
 * Iterates through the hash table and frees all memory blocks
 * contained in it and memory table.
 * 
 * @param memory_table The memory table to free.
 */
void	gc_free_all_mem(t_memory_table *memory_table)
{
	register size_t	i;
	t_memory_block	*block;
	t_memory_block	*next_block;

	i = -1;
	gc_all_table_init(GC_DEL, memory_table);
	while (memory_table && ++i < memory_table->size && memory_table->table)
	{
		block = memory_table->table[i];
		while (block != NULL)
		{
			next_block = block->next;
			if (block->free_fun)
				((void (*)(void *))block->free_fun)(block->info);
			free(block);
			block = next_block;
		}
	}
	if (memory_table)
		free(memory_table->table);
	free(memory_table);
}

/**
 * Free memory allocated by the garbage collector.
 * Iterates through the hash table to find the block corresponding
 * to the specified pointer.
 * 
 * @param ptr The pointer to the memory to free.
 */
void	gc_free(t_memory_table *memory_table, void *ptr)
{
	uint32_t		index;
	t_memory_block	*block;
	t_memory_block	*prev_block;

	if (!ptr || ptr == NULL)
		return ;
	index = hash(memory_table, ptr);
	block = memory_table->table[index];
	prev_block = NULL;
	while (block != NULL)
	{
		if (block->ptr == ptr)
		{
			if (!prev_block)
				memory_table->table[index] = block->next;
			else
				prev_block->next = block->next;
			free_block(block);
			return ;
		}
		prev_block = block;
		block = block->next;
	}
	gc_error("Pointer not found in memory table");
}
