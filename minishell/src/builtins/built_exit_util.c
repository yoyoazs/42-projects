/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit_utile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npigeon <npigeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:02:15 by npigeon           #+#    #+#             */
/*   Updated: 2024/08/01 10:35:37 by npigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/pipex.h"

static int	ft_long_itoa_info(long long int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_long_itoa(long long int n)
{
	char			*str;
	int				size;
	long long int	num;

	num = n;
	size = ft_long_itoa_info(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	while (num != 0 && size > 0)
	{
		str[size - 1] = num % 10 + '0';
		num /= 10;
		size--;
	}
	str[ft_long_itoa_info(n)] = '\0';
	return (str);
}

static int long	fct_long_overf(char **nb, char *argv, unsigned int i)
{
	if (((i < ft_strlen((*nb)) && (*nb)[0] != '-'))
		|| (i < ft_strlen((*nb)) - 1))
		return (1);
	else if ((i > ft_strlen((*nb))
			|| ((i > ft_strlen((*nb)) - 1) && (*nb)[0] == '-')))
		return (0);
	else
	{
		i = 0;
		while (i < ft_strlen((*nb)))
		{
			if ((*argv > (*nb)[i] && (*nb)[0] != '-')
				|| (*argv > (*nb)[i + 1] && (*nb)[0] == '-'))
				return (0);
			if ((*argv < (*nb)[i] && (*nb)[0] != '-')
				|| (*argv > (*nb)[i + 1] && (*nb)[0] == '-'))
				return (1);
			i++;
			argv++;
		}
	}
	return (1);
}

int long long	verif_long_overf(char *argv)
{
	char			*nb;
	int				i;
	int long		res;

	i = 0;
	while (*argv == ' ' || (9 <= *argv && *argv <= 13))
		argv++;
	if (*argv == '-')
		nb = ft_long_itoa(LONG_MIN);
	else
		nb = ft_long_itoa(LONG_MAX);
	if (*argv == '+' || *argv == '-')
		argv++;
	while ('0' == *argv)
		argv++;
	if (*argv == '\0')
	{
		free(nb);
		return (1);
	}
	while (argv[i] >= '0' && argv[i] <= '9')
		i++;
	res = fct_long_overf(&nb, argv, i);
	free(nb);
	return (res);
}

char	*get_from_env(char ***env, char *path_asked)
{
	int	i;

	i = 0;
	if (!*env)
		return (NULL);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], path_asked, ft_strlen(path_asked) - 1) == 0)
			return ((*env)[i] + ft_strlen(path_asked) + 1);
		i++;
	}
	return (NULL);
}
