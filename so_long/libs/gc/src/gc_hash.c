/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   gc_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:58:36 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/23 23:29:30 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Computes the hash of a memory address for a given memory table.
 *
 * @param memory_table   Pointer to the memory table in which the element
 * should be inserted.
 * @param ptr            Pointer to the memory address to hash.
 * @return               The hash of the memory address for the given memory
 * table.
 */
uint32_t	hash(t_memory_table *memory_table, void *ptr)
{
	uintptr_t	address;
	uint32_t	hash;

	hash = 5381;
	address = (uintptr_t)ptr;
	while (address != 0)
	{
		hash = ((hash << 5) + hash) + (uint32_t)(address & 0xFF);
		address >>= 8;
		hash %= memory_table->size;
	}
	return (hash);
}
