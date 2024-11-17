/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:09:30 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/02/07 07:48:15 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	ft_strlen_zero(char *str)
{
	long long	i;
	long long	number_of_zero;

	i = -1;
	number_of_zero = 0;
	if ((str[0] == '-' || str[0] == '+') && str[1])
		i++;
	while (str[++i] && str[i] == '0')
		number_of_zero++;
	while (str[i])
		i++;
	return (i - number_of_zero);
}

int	ft_isint(char *str, char **tab, int size)
{
	int				i;
	const long long	num = ft_atoi(str);

	i = -1;
	if ((str[0] == '-' || str[0] == '+') && str[1])
		i++;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	if (ft_strlen_zero(str) > 11 || num > MAX_INT || num < MIN_INT)
		return (0);
	i = -1;
	while (tab[++i] && i < size)
		if (ft_atoi(tab[i]) == num)
			return (0);
	return (1);
}

char	**get_char(char **str)
{
	char	*args;
	char	**result;
	int		i;

	i = 0;
	args = NULL;
	while (str[++i])
	{
		args = ft_strjoin(args, str[i]);
		if (!args)
			exit_error(0);
		args = ft_strjoin(args, " ");
		if (!args)
			exit_error(0);
	}
	result = ft_split(args, ' ');
	free(args);
	i = -1;
	while (result[++i])
		if (!ft_isint(result[i], result, i))
			return (free_tab(result));
	return (result);
}

char	**handle_args(char **argv)
{
	char	**args;

	args = get_char(argv);
	if (!args)
		exit_error(0);
	if (!(args && args[0]))
	{
		free(args);
		exit(0);
	}
	return (args);
}
