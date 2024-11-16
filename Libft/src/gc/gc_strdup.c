/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:30:28 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/05/17 15:49:31 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_strdup(t_memory_table *memory_table, char *s)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = gc_malloc(memory_table, ft_strlen(s) + 1);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	return (str);
}

void	*gc_strndup(t_memory_table *memory_table, char *s, int len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	str = gc_malloc(memory_table, len + 1);
	ft_strlcpy(str, s, len + 1);
	return (str);
}
