/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:20:34 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/07 10:54:25 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void	gc_exit_main_loop(t_master_memory *master)
{
	register size_t	i;
	t_memory_block	*block;
	t_memory_block	*next_block;
	t_memory_table	*memory_table;	

	i = -1;
	memory_table = master->mem;
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
	master = master->next;
}

/**
 * Free the memory allocated by the garbage collector and exit the program.
 * Iterates through each element of the hash table, frees the memory of each
 * block, and the table itself.
 */
void	gc_exit(int status)
{
	t_master_memory	*master;
	t_master_memory	*current;

	master = gc_all_table_init(GC_GET, NULL);
	current = master;
	while (current)
	{
		gc_exit_main_loop(current);
		current = current->next;
		free(master);
		master = current;
	}
	exit(status);
}
