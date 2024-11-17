/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:32:09 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 23:07:29 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list			args;
	t_flag_field	flag_field;
	unsigned int	n;

	n = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			flag_field = ft_printf_parse_flags(&format);
			if (*format == '*')
				ft_printf_parse_wildcard(&flag_field, args, &format);
			ft_printf_parse_width(&flag_field, &format);
			if (*format == '.')
				ft_printf_parse_precision(&flag_field, &format, args);
			ft_printf_parse_format(flag_field, args, format, &n);
		}
		else
			ft_printf_char_count(*format, &n);
		format++;
	}
	va_end(args);
	return (n);
}
