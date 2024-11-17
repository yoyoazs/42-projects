/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_initialise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 21:17:34 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/07 08:33:18 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static void	del_table(t_master_memory *master, t_memory_table *new_table)
{
	t_master_memory	*tmp;
	t_master_memory	*new;

	tmp = master;
	while (tmp && tmp->next && tmp->next->mem != new_table)
		tmp = tmp->next;
	if (tmp && tmp->next)
	{
		new = tmp->next;
		tmp->next = new->next;
		free(new);
	}
	else
		gc_error("Trying to delete uninitialized table");
}

t_master_memory	*gc_all_table_init(t_gc_type type, t_memory_table *new_table)
{
	static t_master_memory	*master = NULL;
	t_master_memory			*tmp;
	t_master_memory			*new;

	if (type == GC_GET)
		return (master);
	if (type == GC_ADD)
	{
		tmp = master;
		new = (t_master_memory *)malloc(sizeof(t_master_memory));
		if (!new)
			gc_error("Allocation error");
		while (tmp && tmp->next)
			tmp = tmp->next;
		new->mem = new_table;
		new->next = NULL;
		if (!tmp)
			master = new;
		else
			tmp->next = new;
	}
	if (type == GC_DEL)
		del_table(master, new_table);
	return (NULL);
}

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
		gc_error("Allocation error");
	memory_table->size = MEMORY_TABLE_SIZE;
	memory_table->table = (t_memory_block **)ft_calloc(memory_table->size,
			sizeof(t_memory_block *));
	if (memory_table->table == NULL)
		gc_error("Allocation error");
	gc_all_table_init(GC_ADD, memory_table);
	return (memory_table);
}
