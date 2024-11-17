/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:08:38 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/27 00:59:56 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_parse_format(va_list args, const char format)
{
	int		n;

	n = 0;
	if (format == 'c')
		n += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		n += ft_printf_str(va_arg(args, char *));
	else if (format == 'p')
		n += ft_printf_ptr(va_arg(args, unsigned long long));
	else if (format == 'd' || format == 'i')
		n += ft_printf_nbr(va_arg(args, int));
	else if (format == 'u')
		n += ft_printf_uint(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		n += ft_printf_hexa(va_arg(args, unsigned int), format);
	else if (format == '%')
		n += ft_printf_char('%');
	return (n);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			n;

	n = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			n += ft_printf_parse_format(args, *format);
		}
		else
			n += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (n);
}
