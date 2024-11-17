/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:28:44 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/05/21 19:13:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_extention(char *nl, char *line, char *buf)
{
	int	to_copy;

	if (ft_strlen(line) == 0)
	{
		free(line);
		return (0);
	}
	if (nl != NULL)
	{
		to_copy = nl - line + 1;
		ft_strcpy(buf, nl + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
	return (to_copy);
}

char	*join_gnl(size_t *len, char *line, char *buf)
{
	char			*tmp;
	const size_t	len_line = ft_strlen(line) + ft_strlen(buf);

	if (len_line + 1 > *len)
	{
		while (len_line >= *len)
			(*len) = (*len) * 2;
		tmp = malloc((len_line + 1 + *len) * sizeof(char));
		if (!tmp)
		{
			free(line);
			return (NULL);
		}
		ft_strlcpy(tmp, line, *len);
		free(line);
		line = tmp;
	}
	ft_strlcat(line, buf, *len);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	size_t		i;
	char		*line;
	int			extension;
	int			c;

	extension = 0;
	i = BUFFER_SIZE;
	line = ft_strdup(buf);
	c = 1;
	while (!(ft_strchr(line, '\n')) && (c))
	{
		c = read(fd, buf, BUFFER_SIZE);
		buf[c] = '\0';
		line = join_gnl(&i, line, buf);
		if (!line)
			return (NULL);
	}
	extension = gnl_extention(ft_strchr(line, '\n'), line, buf);
	if (extension == 0)
		return (NULL);
	line[extension] = '\0';
	return (line);
}
