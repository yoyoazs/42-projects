/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 02:30:12 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 23:48:29 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_str_count(char *str, unsigned int *n)
{
	ft_putstr_fd(str, 1);
	*n += ft_strlen(str);
}

static void	ft_printf_put_str(t_flag_field flag_field, char *str,
unsigned int *n)
{
	char	*temp;

	if (flag_field.precision == 0)
		ft_printf_str_count(str, n);
	else
	{
		temp = ft_substr(str, 0, flag_field.precision);
		ft_printf_str_count(temp, n);
		free(temp);
	}
}

void	ft_printf_str(char *str, unsigned int *n, t_flag_field flag_field)
{
	int	len;

	if (!str)
	{
		free(str);
		str = ft_strdup(NULL_STRING);
	}
	len = ft_strlen(str);
	if (flag_field.dot && (flag_field.precision == 0
			|| (flag_field.precision < (int)ft_strlen(str)
				&& ft_strncmp(str, NULL_STRING, 6) == 0)))
	{
		free(str);
		str = ft_strdup("");
		len = 0;
	}
	if (flag_field.precision > 0 && flag_field.precision < len)
		len = flag_field.precision;
	if (flag_field.left_align)
		ft_printf_put_str(flag_field, str, n);
	while (flag_field.width-- > len)
		ft_printf_char_count(' ', n);
	if (!flag_field.left_align)
		ft_printf_put_str(flag_field, str, n);
	free(str);
}

void	ft_printf_str_without_malloc(char *str, unsigned int *n,
t_flag_field flag_field)
{
	char	*newstr;

	if (!str)
	{
		newstr = ft_strdup(NULL_STRING);
	}
	else
		newstr = ft_strdup(str);
	ft_printf_str(newstr, n, flag_field);
}
