/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:13:25 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/03/30 19:13:36 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define NULL_STRING "(null)"
# define SPECIAL_FLAGS "-.0# +"
# define HEXADECIMAL "0123456789abcdef"

typedef struct s_flag_field
{
	int		width;
	int		precision;
	bool	left_align;
	bool	zero_padding;
	bool	hash_flag;
	bool	dot;
	bool	number_after_dot;
	bool	space_flag;
	bool	plus_flag;
	char	type;
}	t_flag_field;

typedef struct s_data
{
	int	i;
	int	j;
	int	neg;
	int	len;
}	t_data;

int				ft_hexlen(unsigned int n);
int				ft_ptrlen(unsigned long int num);
char			*ft_uitoa(unsigned int n);
int				ft_ulen(unsigned int num);
int				ft_printf(const char *format, ...);
void			ft_printf_hex(unsigned int num, unsigned int *n, char format,
					t_flag_field flag_field);
void			ft_printf_number(int num, unsigned int *n,
					t_flag_field flag_field);
void			ft_printf_ptr(unsigned long int ptr, unsigned int *n,
					t_flag_field flag_field);
void			ft_put_ptr(unsigned long int num, unsigned int *n,
					t_flag_field flag_field);
void			ft_printf_unsigned(unsigned int num, unsigned int *n,
					t_flag_field flag_field);
void			ft_printf_str(char *str, unsigned int *n,
					t_flag_field flag_field);
t_flag_field	ft_init_struct(void);
void			ft_printf_char(char c, unsigned int *n,
					t_flag_field flag_field);
void			ft_printf_char_count(char c, unsigned int *n);
void			ft_printf_str_count(char *str, unsigned int *n);
void			ft_printf_bonus(char *str, unsigned int *n,
					t_flag_field flag_field, const int i);
void			ft_printf_str_count(char *str, unsigned int *n);
void			ft_printf_str_without_malloc(char *str, unsigned int *n,
					t_flag_field flag_field);
t_flag_field	ft_printf_parse_flags(const char **format);
void			ft_printf_parse_width(t_flag_field *flag_field,
					const char **format);
void			ft_printf_parse_format(t_flag_field flag_field, va_list args,
					const char *format, unsigned int *n);
void			ft_printf_parse_precision(t_flag_field *flag_field,
					const char **format, va_list args);
void			ft_printf_parse_wildcard(t_flag_field *flag_field, va_list args,
					const char **format);
t_data			ft_init_data(void);

#endif