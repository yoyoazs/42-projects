/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 18:58:29 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 10:34:33 by ybeaucou         ###   ########.fr       */
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
	ptr = malloc(size);
	if (!ptr)
		gc_error(memory_table, "Allocation error");
	index = hash(memory_table, ptr);
	new_block = malloc(sizeof(t_memory_block));
	if (!new_block)
	{
		free(ptr);
		gc_error(memory_table, "Allocation error");
	}
	new_block->ptr = ptr;
	new_block->free_fun = NULL;
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

void	*gc_strdup(t_memory_table *memory_table, char *s)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = gc_malloc(memory_table, ft_strlen(s) + 1);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	return (str);
}

void	*gc_strjoin(t_memory_table *memory_table, char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL)
		return (gc_strdup(memory_table, s2));
	if (s2 == NULL)
		return (NULL);
	str = (char *)gc_malloc(memory_table, sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	gc_free(memory_table, s1);
	return (str);
}
