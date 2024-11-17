/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:14:23 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/27 08:21:07 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	write_string(t_game *data, int fd, const char *str)
{
	const size_t	len = ft_strlen(str);

	if (write(fd, str, len) != (ssize_t)len)
		error_map(data, "Error while writing in file.");
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	return (str);
}

char	*ms_to_time(unsigned long long ms)
{
	char	*hour;
	char	*min;
	char	*sec;
	char	*str;

	hour = ft_itoa((ms / (1000 * 60 * 60)) / 60);
	min = ft_itoa((ms / (1000 * 60)) % 60);
	sec = ft_itoa((ms / 1000) % 60);
	if (ft_strlen(hour) == 1)
		hour = strjoin_free(ft_strdup("0"), hour);
	if (ft_strlen(min) == 1)
		min = strjoin_free(ft_strdup("0"), min);
	if (ft_strlen(sec) == 1)
		sec = strjoin_free(ft_strdup("0"), sec);
	str = ft_strjoin(hour, ":");
	str = strjoin_free(str, min);
	str = ft_strjoin(str, ":");
	str = strjoin_free(str, sec);
	return (str);
}
