/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 00:08:03 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/11/27 01:00:53 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>
# include "../../libft/includes/libft.h"

# define HEXADECIMAL "0123456789abcdef"

int	ft_printf(const char *format, ...);
int	ft_printf_char(char c);
int	ft_printf_str(char *str);
int	ft_printf_nbr(int n);
int	ft_printf_uint(unsigned int n);
int	ft_printf_hexa(unsigned int n, char c);
int	ft_printf_ptr(unsigned long long n);

#endif