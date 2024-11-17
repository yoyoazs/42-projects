/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:20:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 23:44:36 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_ptr(unsigned long int num, unsigned int *n,
t_flag_field flag_field)
{
	char	*hex_digits;
	int		i;

	hex_digits = malloc(sizeof(char) * (ft_ptrlen(num) + 3));
	if (!hex_digits)
		return ;
	i = ft_ptrlen(num) + 2;
	hex_digits[i] = '\0';
	hex_digits[0] = '0';
	hex_digits[1] = 'x';
	while (num)
	{
		hex_digits[--i] = HEXADECIMAL[num % 16];
		num /= 16;
	}
	ft_printf_str(hex_digits, n, flag_field);
}

void	ft_printf_ptr(unsigned long int ptr, unsigned int *n,
t_flag_field flag_field)
{
	if (ptr == 0)
		return (ft_printf_str_without_malloc("(nil)", n, flag_field));
	ft_put_ptr(ptr, n, flag_field);
}
