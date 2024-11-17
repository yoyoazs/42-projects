/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:02:47 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/05 13:01:19 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_parse_wildcard(t_flag_field *flag_field, va_list args,
const char **format)
{
	(*format)++;
	if (flag_field->dot)
	{
		flag_field->precision = va_arg(args, int);
		if (flag_field->precision < 0)
		{
			flag_field->precision = 0;
			flag_field->dot = false;
		}
	}
	else
	{
		flag_field->width = va_arg(args, int);
		if (flag_field->width < 0)
		{
			flag_field->width *= -1;
			flag_field->left_align = true;
			flag_field->zero_padding = false;
		}
	}
}

void	ft_printf_parse_precision(t_flag_field *flag_field, const char **format,
va_list args)
{
	(*format)++;
	flag_field->dot = 1;
	if (ft_isdigit(**format))
	{
		while (ft_isdigit(**format))
		{
			flag_field->precision *= 10;
			flag_field->precision += **format - '0';
			(*format)++;
		}
		flag_field->number_after_dot = true;
	}
	if (**format == '*')
	{
		flag_field->precision = va_arg(args, int);
		if (flag_field->precision < 0)
		{
			flag_field->precision = 0;
			flag_field->dot = false;
		}
		(*format)++;
	}
}

void	ft_printf_parse_format(t_flag_field flag_field, va_list args,
const char *format, unsigned int *n)
{
	flag_field.type = *format;
	if (*format == 'c')
		ft_printf_char(va_arg(args, int), n, flag_field);
	else if (*format == 's')
		ft_printf_str_without_malloc(va_arg(args, char *), n, flag_field);
	else if (*format == 'p')
		ft_printf_ptr(va_arg(args, unsigned long long), n, flag_field);
	else if (*format == 'd' || *format == 'i')
		ft_printf_number(va_arg(args, int), n, flag_field);
	else if (*format == 'u')
		ft_printf_unsigned(va_arg(args, unsigned int), n, flag_field);
	else if (*format == 'x' || *format == 'X')
		ft_printf_hex(va_arg(args, unsigned int), n, *format, flag_field);
	else if (*format == '%')
		ft_printf_char('%', n, flag_field);
}

void	ft_printf_parse_width(t_flag_field *flag_field, const char **format)
{
	while (ft_isdigit(**format))
	{
		if (flag_field->dot)
		{
			flag_field->precision *= 10;
			flag_field->precision += **format - '0';
		}
		else
			flag_field->width = flag_field->width * 10 + (**format - '0');
		(*format)++;
	}
}

t_flag_field	ft_printf_parse_flags(const char **format)
{
	t_flag_field	flag_field;

	flag_field = ft_init_struct();
	while (**format && ft_strchr(SPECIAL_FLAGS, **format))
	{
		if (**format == '-')
			flag_field.left_align = true;
		else if (**format == '0')
			flag_field.zero_padding = true;
		else if (**format == '.')
		{
			flag_field.dot = true;
			if (*(*format + 1) >= '0' && *(*format + 1) <= '9')
				flag_field.number_after_dot = true;
		}
		else if (**format == '#')
			flag_field.hash_flag = true;
		else if (**format == ' ')
			flag_field.space_flag = true;
		else if (**format == '+')
			flag_field.plus_flag = true;
		(*format)++;
	}
	return (flag_field);
}
