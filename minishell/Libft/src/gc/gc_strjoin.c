/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:39:24 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/01 08:47:16 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*gc_strnjoin(t_memory_table *mem_table, char *s1, char *s2, size_t len)
{
	char	*str;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (gc_strdup(mem_table, s2));
	str = (char *)gc_malloc(mem_table, sizeof(char)
			* (ft_strlen(s1) + len + 1));
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + len + 1);
	gc_free(mem_table, s1);
	return (str);
}

void	*gc_strjoin(t_memory_table *mem_table, char *s1, char *s2)
{
	char	*str;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (gc_strdup(mem_table, s2));
	str = (char *)gc_malloc(mem_table, sizeof(char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	gc_free(mem_table, s1);
	return (str);
}

void	*gc_strjoin_char(t_memory_table *mem_table, char *s1, char s2)
{
	char	str[2];

	if (s2 == '\0')
		return (gc_strdup(mem_table, s1));
	str[0] = s2;
	str[1] = '\0';
	if (s1 == NULL)
		return (gc_strdup(mem_table, str));
	return (gc_strjoin(mem_table, s1, str));
}
