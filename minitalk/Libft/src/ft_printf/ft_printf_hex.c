/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:07:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/10 18:25:25 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strtoupper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		str[i] = ft_toupper(str[i]);
}

static void	ft_printf_hex_zero(unsigned int *n, t_flag_field flag_field)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	str[0] = '0';
	str[1] = '\0';
	ft_printf_bonus(str, n, flag_field, 1);
}

static void	ft_printf_hex_hashflag(char *str, unsigned int *n,
t_flag_field flag_field, int len)
{
	char	*result;

	result = malloc(sizeof(char) * (len + 3));
	result[0] = '0';
	result[1] = flag_field.type;
	result[len + 2] = '\0';
	while (len--)
		result[len + 2] = str[len];
	ft_printf_bonus(result, n, flag_field, ft_strlen(result));
	free(str);
}

void	ft_printf_hex(unsigned int num, unsigned int *n, char format,
t_flag_field flag_field)
{
	char		*str;
	const int	len = ft_hexlen(num);
	int			i;

	if (num == 0)
		return (ft_printf_hex_zero(n, flag_field));
	i = len;
	str = (char *)malloc(i + 1);
	if (!str)
		return ;
	ft_memset(str, ' ', i + 1);
	str[i] = '\0';
	while (num)
	{
		str[--i] = HEXADECIMAL[num % 16];
		num /= 16;
	}
	if (format == 'X')
		ft_strtoupper(str);
	if (flag_field.hash_flag == 1 && str[0] != '0')
		return (ft_printf_hex_hashflag(str, n, flag_field, len));
	ft_printf_bonus(str, n, flag_field, len);
}
