/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_add_memory_block.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 13:55:04 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:34:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Adds a memory block to a given memory table.
 *
 * This function adds a new memory block to the specified memory table.
 * The memory block contains information about the allocated memory, including
 * the pointer to the allocated memory, an associated function (optional), and
 * associated arguments (optional).
 *
 * @param memory_table   Pointer to the memory table to which to add the block.
 * @param ptr            Pointer to the allocated memory.
 * @param fun            Pointer to an associated function (optional).
 * @param args           Pointer to associated arguments (optional).
 */
void	gc_add_memory_block(t_memory_table *memory_table, void *ptr,
void (*free_func)(t_block_info *), t_block_info *info)
{
	t_memory_block	*new_block;

	if (ptr == NULL || free_func == NULL || info == NULL)
		return ;
	new_block = (t_memory_block *)malloc(sizeof(t_memory_block));
	if (new_block == NULL)
		gc_exit(memory_table);
	new_block->info = (t_block_info *)gc_malloc(memory_table,
			sizeof(t_block_info));
	*(new_block->info) = *info;
	new_block->free_fun = free_func;
	new_block->next = memory_table->table[0];
	memory_table->table[0] = new_block;
}
