/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:49:11 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/12 03:41:30 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*join;
	long int		i;
	const long int	len1 = ft_strlen(s1);
	const long int	len2 = ft_strlen(s2);

	join = malloc(len1 + len2 + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	i = -1;
	while (s2[++i])
		join[len1 + i] = s2[i];
	join[len1 + len2] = '\0';
	return (join);
}
