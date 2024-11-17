/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_init_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:58:59 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/26 14:37:10 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			break ;
		tmp[count] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (buffer == NULL)
			break ;
	}
	free(tmp);
	return (buffer);
}
