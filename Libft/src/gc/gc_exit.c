/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:20:34 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/11/05 10:50:03 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Free the memory allocated by the garbage collector and exit the program.
 * Iterates through each element of the hash table, frees the memory of each
 * block, and the table itself.
 */
void	gc_exit(t_memory_table *memory_table, int res)
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
	if (memory_table)
		free(memory_table->table);
	free(memory_table);
	exit(res);
}
