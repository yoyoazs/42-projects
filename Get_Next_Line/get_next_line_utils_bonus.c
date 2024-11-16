/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:28:27 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/03 15:15:17 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

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

char	*ft_strjoin(char *s1, char *s2, int len2)
{
	char			*join;
	long int		i;
	long int		len1;

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
