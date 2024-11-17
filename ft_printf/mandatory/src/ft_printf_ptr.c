/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:44:20 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/27 01:00:28 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_ptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_printf_ptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	print_length += write(1, "0x", 2);
	ft_put_ptr(ptr);
	print_length += ft_ptrlen(ptr);
	return (print_length);
}
