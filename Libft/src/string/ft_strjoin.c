/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:49:11 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/11/14 10:50:12 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*join;
	long int		i;
	long int		len1;
	const long int	len2 = ft_strlen(s2);

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
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
	free(s1);
	return (join);
}

char	*ft_strjoin_no_free(char *s1, char *s2)
{
	char			*join;
	long int		i;
	long int		len1;
	const long int	len2 = ft_strlen(s2);

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
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
