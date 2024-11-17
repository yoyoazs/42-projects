/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:14:07 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 18:49:13 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_char_count(char c, unsigned int *n)
{
	ft_putchar_fd(c, 1);
	*n += 1;
}

void	ft_printf_char(char c, unsigned int *n, t_flag_field flag_field)
{
	if (flag_field.left_align == 1)
		ft_printf_char_count(c, n);
	while (flag_field.width-- > 1)
	{
		if (flag_field.zero_padding == 1)
			ft_printf_char_count('0', n);
		else
			ft_printf_char_count(' ', n);
	}
	if (flag_field.left_align == 0)
		ft_printf_char_count(c, n);
}
