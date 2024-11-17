/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 22:07:51 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/05 13:00:55 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_printf_bonus_sign(char **str, t_flag_field flag_field, int neg)
{
	int	j;

	if (flag_field.left_align == 1)
	{
		if (neg)
			(*str)[0] = '-';
		else
			(*str)[0] = '+';
	}
	else
	{
		j = ft_strlen(*str) - 1;
		while (j >= 0 && ft_isdigit((*str)[j]))
			j--;
		if (j < 0)
			j = 0;
		if (neg)
			(*str)[j] = '-';
		else
			(*str)[j] = '+';
	}
}

void	ft_printf_bonus_neg(char **str, t_flag_field *flag_field, t_data *data)
{
	char	*tmp;

	data->neg = 1;
	tmp = ft_substr(*str, 1, ft_strlen(*str));
	free(*str);
	*str = ft_strdup(tmp);
	free(tmp);
	data->j--;
	if (flag_field->precision > 0
		&& flag_field->precision > (int)ft_strlen(*str))
	{
		data->len++;
		flag_field->precision++;
		flag_field->width++;
	}
	if (flag_field->width > flag_field->precision
		&& flag_field->precision > (int)ft_strlen(*str))
		data->len--;
}

void	ft_printf_bonus_terms(t_flag_field *flag_field, char **str,
t_data *data, unsigned int *n)
{
	if (data->len < flag_field->precision)
		data->len = flag_field->precision;
	if (data->len < flag_field->width)
		data->len = flag_field->width;
	if (flag_field->plus_flag && (*str)[0] != '-')
		data->len++;
	if (flag_field->space_flag && (*str)[0] != '-')
	{
		*n += write(1, " ", 1);
		if (flag_field->left_align
			&& (flag_field->width >= flag_field->precision))
			data->len--;
		if (flag_field->zero_padding && flag_field->width > (int)ft_strlen(*str)
			&& flag_field->width > flag_field->precision)
			data->len--;
	}
	if ((*str)[0] == '-' && (flag_field->type == 'd'
		|| flag_field->type == 'i'))
		ft_printf_bonus_neg(str, flag_field, data);
}

void	ft_printf_bonus2(t_flag_field *flag_field, char **result,
t_data *data, char *str)
{
	if ((flag_field->zero_padding == 1 && flag_field->left_align == 0
			&& !flag_field->dot))
		ft_memset(*result, '0', data->len);
	else
		ft_memset(*result, ' ', data->len);
	(*result)[data->len--] = '\0';
	if (flag_field->dot && flag_field->precision == 0 && str && str[0] == '0'
		&& !str[1] && flag_field->space_flag == 0)
		str[0] = ' ';
	if (flag_field->left_align == 1)
	{
		data->len = data->i;
		if (flag_field->precision > data->i)
			data->len = flag_field->precision;
		data->len--;
	}
	while (str && data->j >= 0 && str[data->j])
		(*result)[data->len--] = str[data->j--];
	while (flag_field->precision-- > data->i)
		(*result)[data->len--] = '0';
	if (data->neg || (flag_field->plus_flag && str[0] != '-'))
		ft_printf_bonus_sign(result, *flag_field, data->neg);
}

void	ft_printf_bonus(char *str, unsigned int *n,
t_flag_field flag_field, const int i)
{
	char	*result;
	t_data	data;

	data = ft_init_data();
	data.i = i;
	data.j = ft_strlen(str) - 1;
	data.len = i;
	ft_printf_bonus_terms(&flag_field, &str, &data, n);
	if (flag_field.width == 0 && flag_field.precision == 0 && str[0] == '0'
		&& !str[1] && flag_field.dot && !flag_field.space_flag)
	{
		free(str);
		return ;
	}
	result = malloc(sizeof(char) * data.len + 1);
	if (!result)
	{
		free(str);
		return ;
	}
	ft_printf_bonus2(&flag_field, &result, &data, str);
	ft_printf_str_count(result, n);
	free(result);
	free(str);
}
