/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:28:46 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/08/12 01:09:51 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_chineese(unsigned char *bytes)
{
	if ((bytes[0] == 0xE4 && bytes[1] >= 0xB8 && bytes[1] <= 0xBF
			&& bytes[2] >= 0x80 && bytes[2] <= 0xBF) || (bytes[0] == 0xE5
			&& bytes[1] >= 0x80 && bytes[1] <= 0xA3 && bytes[2] >= 0x80
			&& bytes[2] <= 0xBF) || (bytes[0] == 0xE9 && bytes[1] == 0xBE
			&& bytes[2] >= 0x80 && bytes[2] <= 0x9E && bytes[3] >= 0x80
			&& bytes[3] <= 0xBF) || (bytes[0] == 0xE9 && bytes[1] == 0xBE
			&& bytes[2] == 0x99 && bytes[3] >= 0x80 && bytes[3] <= 0xBF)
		|| (bytes[0] == 0xE3 && bytes[1] >= 0x8D && bytes[1] <= 0xA3
			&& bytes[2] >= 0x80 && bytes[2] <= 0xBF) || (bytes[0] == 0xE4
			&& bytes[1] >= 0xB0 && bytes[1] <= 0xB9 && bytes[2] >= 0x80
			&& bytes[2] <= 0xBF) || (bytes[0] == 0xE5 && bytes[1] == 0x9B
			&& bytes[2] >= 0xBE && bytes[2] <= 0xBF) || (bytes[0] == 0xF0
			&& bytes[1] == 0xA0 && bytes[2] >= 0x80 && bytes[2] <= 0x8F
			&& bytes[3] >= 0x80 && bytes[3] <= 0xBF) || (bytes[0] == 0xF0
			&& bytes[1] == 0xAA && bytes[2] >= 0x8C && bytes[2] <= 0x8F
			&& bytes[3] >= 0x80 && bytes[3] <= 0xBF) || (bytes[0] == 0xF0
			&& bytes[1] == 0xAB && bytes[2] >= 0x9E && bytes[2] <= 0xA1
			&& bytes[3] >= 0x80 && bytes[3] <= 0xBF))
		return (true);
	return (false);
}

static bool	is_emoji_2(unsigned char *bytes)
{
	if (bytes[0] == 0xE2 && bytes[1] == 0x9C && bytes[2] >= 0xA2
		&& bytes[2] <= 0xB0)
		return (true);
	else if (bytes[0] == 0xE2 && bytes[1] == 0x93 && bytes[2] >= 0x82
		&& bytes[2] <= 0xA1)
		return (true);
	else if (bytes[0] == 0xC2 && bytes[1] == 0xA9
		&& ((bytes[2] == 0xE2 && bytes[3] >= 0x9D && bytes[3] <= 0xBF)
			|| (bytes[2] >= 0xF0 && bytes[2] <= 0xF3)))
		return (true);
	return (is_chineese(bytes));
}

static bool	is_emoji(const char *text, int index)
{
	unsigned char	bytes[4];

	if (text[index])
		bytes[0] = text[index];
	if (text[index] && text[index + 1])
		bytes[1] = text[index + 1];
	if (text[index] && text[index + 1] && text[index + 2])
		bytes[2] = text[index + 2];
	if (text[index] && text[index + 1] && text[index + 2] && text[index + 3])
		bytes[3] = text[index + 3];
	if (bytes[0] == 0xF0 && bytes[1] == 0x9F)
	{
		if ((bytes[2] >= 0x98 && bytes[2] <= 0xAF && bytes[3] >= 0x81
				&& bytes[3] <= 0xBF) || (bytes[2] >= 0x80 && bytes[2] <= 0xA0
				&& bytes[3] >= 0x80 && bytes[3] <= 0xBF) || (bytes[2] >= 0x98
				&& bytes[2] <= 0xB6) || (bytes[2] >= 0x9A && bytes[2] <= 0xA5
				&& bytes[3] >= 0x81 && bytes[3] <= 0xBF) || (bytes[2] >= 0x8C
				&& bytes[2] <= 0xAF && bytes[3] >= 0x81 && bytes[3] <= 0xBF))
			return (true);
	}
	return (is_emoji_2(bytes));
}

size_t	len_string_8(const char *text, size_t index)
{
	size_t	length;
	size_t	i;

	i = -1;
	length = 0;
	while (text[++i] != '\0' && i < index)
	{
		if (is_emoji(text, i))
		{
			length++;
			i += 3;
		}
		else if ((text[i] & 0xC0) == 0x80 || (text[i] & 0xF8) == 0xF0)
			continue ;
		else if ((text[i] & 0xE0) == 0xC0)
			i += 1;
		else if ((text[i] & 0xF0) == 0xE0)
			i += 2;
		length++;
	}
	return (length);
}
