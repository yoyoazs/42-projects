/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:41:13 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 23:28:18 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str2;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str2 = (char *)malloc(len + 1);
	if (str2 == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		str2[i] = s[i + start];
	str2[len] = '\0';
	return (str2);
}
