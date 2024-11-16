/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:23:21 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/05/24 11:08:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	i;
	char	*str2;

	len = ft_strlen(str);
	i = -1;
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
		return (NULL);
	while (++i < len)
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}
