/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:28:44 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/20 10:30:32 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*init_buffer(int fd, char *buffer)
{
	char	*tmp;
	int		count;

	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	count = 1;
	while (!ft_strchr(buffer, '\n') && count != 0)
	{
		count = read(fd, tmp, BUFFER_SIZE);
		if (count == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[count] = '\0';
		buffer = ft_strjoin(buffer, tmp, count);
	}
	free(tmp);
	return (buffer);
}

char	*get_new_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (buffer[++i] && buffer[i] != '\n')
		str[i] = buffer[i];
	if (buffer[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*set_new_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	tmp[j] = '\0';
	free(buffer);
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[MAX_FD];

	if (fd < 0 || fd >= MAX_FD || MAX_FD <= 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer[fd] = init_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_new_line(buffer[fd]);
	buffer[fd] = set_new_buffer(buffer[fd]);
	return (line);
}
