/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:45:18 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/28 13:04:01 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_number(int num, unsigned int *n, t_flag_field flag_field)
{
	char	*str;

	str = ft_itoa(num);
	ft_printf_bonus(str, n, flag_field, ft_strlen(str));
}
