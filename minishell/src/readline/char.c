/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:29:38 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/19 16:36:24 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_bytes_to_read(unsigned char *c, int *unicode)
{
	static const unsigned char	masks[] = {0b10000000, 0b11100000, 0b11110000,
		0b11111000, 0b11111100, 0b11111110};
	static const unsigned char	values[] = {0b00000000, 0b11000000, 0b11100000,
		0b11110000, 0b11111000, 0b11111100};
	int							i;

	if (read(STDIN_FILENO, c, 1) != 1)
		return (-1);
	i = -1;
	while (++i < 6)
	{
		if ((*c & masks[i]) == values[i])
		{
			*unicode = *c & ~masks[i];
			if (i == 0)
				return (0);
			return (i + 1);
		}
	}
	return (-1);
}

int	read_key(void)
{
	unsigned char	c;
	int				bytes_to_read;
	int				unicode;
	unsigned char	utf8[6];
	int				i;

	bytes_to_read = get_bytes_to_read(&c, &unicode);
	if (bytes_to_read == 0)
		return (c);
	else if (bytes_to_read == -1)
		return (-1);
	utf8[0] = c;
	i = 0;
	while (++i < bytes_to_read)
		if (read(STDIN_FILENO, &utf8[i], 1) != 1)
			return (-1);
	i = 0;
	while (++i < bytes_to_read)
	{
		unicode <<= 6;
		unicode |= (utf8[i] & 0b00111111);
	}
	return (unicode);
}

size_t	after_char(t_readline *rl, size_t index)
{
	size_t	i;

	i = index;
	while (rl->input[i] && (rl->input[i + 1] & 0xC0) == 0x80)
		i++;
	if (i == index)
		return (0);
	return (i - index);
}

static int	get_bytes_2(int unicode, unsigned char *bytes)
{
	if (unicode < 0x10000)
	{
		bytes[0] = (unsigned char)(0xE0 | (unicode >> 12));
		bytes[1] = (unsigned char)(0x80 | ((unicode >> 6) & 0x3F));
		bytes[2] = (unsigned char)(0x80 | (unicode & 0x3F));
		bytes[3] = 0;
		return (3);
	}
	else if (unicode < 0x110000)
	{
		bytes[0] = (unsigned char)(0xF0 | (unicode >> 18));
		bytes[1] = (unsigned char)(0x80 | ((unicode >> 12) & 0x3F));
		bytes[2] = (unsigned char)(0x80 | ((unicode >> 6) & 0x3F));
		bytes[3] = (unsigned char)(0x80 | (unicode & 0x3F));
		bytes[4] = 0;
		return (4);
	}
	return (0);
}

int	get_bytes(int unicode, unsigned char *bytes)
{
	if (unicode < 0x80)
	{
		bytes[0] = (unsigned char)unicode;
		bytes[1] = 0;
		return (1);
	}
	else if (unicode < 0x800)
	{
		bytes[0] = (unsigned char)(0xC0 | (unicode >> 6));
		bytes[1] = (unsigned char)(0x80 | (unicode & 0x3F));
		bytes[2] = 0;
		return (2);
	}
	return (get_bytes_2(unicode, bytes));
}
