/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 20:58:41 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/05 13:02:35 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_flag_field	ft_init_struct(void)
{
	t_flag_field	flag_field;

	flag_field.width = 0;
	flag_field.precision = 0;
	flag_field.left_align = false;
	flag_field.zero_padding = false;
	flag_field.hash_flag = false;
	flag_field.space_flag = false;
	flag_field.plus_flag = false;
	flag_field.dot = false;
	flag_field.number_after_dot = false;
	flag_field.type = '0';
	return (flag_field);
}

t_data	ft_init_data(void)
{
	t_data	data;

	data.i = 0;
	data.j = 0;
	data.neg = 0;
	data.len = 0;
	return (data);
}
