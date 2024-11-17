/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_initialise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:34 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 09:57:31 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Initialize the garbage collector.
 * If the garbage collector is already initialized, exits the program with an
 * error message.
 * Allocates memory for the hash table and initializes it to NULL.
 */
t_memory_table	*gc_init(void)
{
	t_memory_table	*memory_table;

	memory_table = malloc(sizeof(t_memory_table));
	if (memory_table == NULL)
		gc_error(memory_table, "Allocation error");
	memory_table->size = MEMORY_TABLE_SIZE;
	memory_table->table = (t_memory_block **)ft_calloc(memory_table->size,
			sizeof(t_memory_block *));
	if (memory_table->table == NULL)
		gc_error(memory_table, "Allocation error");
	return (memory_table);
}
