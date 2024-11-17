/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:38:04 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/26 23:07:06 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_unsigned(unsigned int num, unsigned int *n,
t_flag_field flag_field)
{
	char	*str;

	str = ft_uitoa(num);
	ft_printf_bonus(str, n, flag_field, ft_ulen(num));
}
