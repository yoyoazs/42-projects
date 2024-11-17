/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 22:08:13 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/01 08:36:40 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

/**
 * Display an error message and exit the program.
 * 
 * @param msg The error message to display.
 */
void	gc_error(char *msg)
{
	printf("\033[1;31mErreur:\033[0m %s\n", msg);
	gc_exit(1);
}
