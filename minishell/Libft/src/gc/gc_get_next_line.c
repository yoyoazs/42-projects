/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 08:37:53 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/01 08:44:55 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

static int	gc_gnl_extention(t_memory_table *mem, char *nl, char *ln, char *buf)
{
	int	to_copy;

	if (ft_strlen(ln) == 0)
	{
		gc_free(mem, ln);
		return (0);
	}
	if (nl != NULL)
	{
		to_copy = nl - ln + 1;
		ft_strcpy(buf, nl + 1);
	}
	else
	{
		to_copy = ft_strlen(ln);
		buf[0] = '\0';
	}
	return (to_copy);
}

static char	*gc_join_gnl(t_memory_table *mem, size_t *len, char *ln, char *buf)
{
	char			*tmp;
	const size_t	len_line = ft_strlen(ln) + ft_strlen(buf);

	if (len_line + 1 > *len)
	{
		while (len_line >= *len)
			(*len) = (*len) * 2;
		tmp = gc_malloc(mem, (len_line + 1 + *len) * sizeof(char));
		if (!tmp)
		{
			gc_free(mem, ln);
			return (NULL);
		}
		ft_strlcpy(tmp, ln, *len);
		gc_free(mem, ln);
		ln = tmp;
	}
	ft_strlcat(ln, buf, *len);
	return (ln);
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
		line = gc_join_gnl(mem, &i, line, buf);
		if (!line)
			return (NULL);
	}
	extension = gc_gnl_extention(mem, ft_strchr(line, '\n'), line, buf);
	if (extension == 0)
		return (NULL);
	line[extension] = '\0';
	return (line);
}
