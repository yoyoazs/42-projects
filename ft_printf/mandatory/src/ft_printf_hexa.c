/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:46:45 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/27 01:00:35 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_strtoupper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
}

int	ft_printf_hexa(unsigned int num, char format)
{
	int		len;
	char	*str;

	len = 0;
	if (num == 0)
		return (write(1, "0", 1));
	len = ft_hexlen(num);
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	ft_memset(str, ' ', len + 1);
	str[len] = '\0';
	while (num)
	{
		str[--len] = HEXADECIMAL[num % 16];
		num /= 16;
	}
	if (format == 'X')
		ft_strtoupper(str);
	len = ft_printf_str(str);
	free(str);
	return (len);
}
