/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:56:22 by npigeon           #+#    #+#             */
/*   Updated: 2024/11/05 11:15:09 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

int	gnl_extention(t_memory_table *mem, char *nl, char *line, char *buf)
{
	int	to_copy;

	if (ft_strlen(line) == 0)
		return (gc_free(mem, line), 0);
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

char	*join_gnl(t_memory_table *mem, size_t *len, char *line, char *buf)
{
	char			*tmp;
	const size_t	len_line = ft_strlen(line) + ft_strlen(buf);

	if (len_line + 1 > *len)
	{
		while (len_line >= *len)
			(*len) = (*len) * 2;
		tmp = gc_malloc(mem, (len_line + 1 + *len) * sizeof(char));
		if (!tmp)
		{
			gc_free(mem, line);
			return (NULL);
		}
		ft_strlcpy(tmp, line, *len);
		gc_free(mem, line);
		line = tmp;
	}
	ft_strlcat(line, buf, *len);
	return (line);
}

char	*gc_get_next_line(t_memory_table *mem, int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	size_t		i;
	char		*line;
	int			extension;
	int			c;

	extension = 0;
	i = BUFFER_SIZE;
	line = gc_strdup(mem, buf);
	c = 1;
	while (!(ft_strchr(line, '\n')) && (c))
	{
		c = read(fd, buf, BUFFER_SIZE);
		buf[c] = '\0';
		line = join_gnl(mem, &i, line, buf);
		if (!line)
			return (NULL);
	}
	extension = gnl_extention(mem, ft_strchr(line, '\n'), line, buf);
	if (extension == 0)
		return (NULL);
	line[extension] = '\0';
	return (line);
}
