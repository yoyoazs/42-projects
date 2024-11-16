/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:08:13 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/11/05 10:50:31 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Display an error message and exit the program.
 * 
 * @param msg The error message to display.
 */
void	gc_error(t_memory_table *memory_table, char *msg)
{
	printf("\033[1;31mErreur:\033[0m %s\n", msg);
	gc_exit(memory_table, 1);
}
