/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:00:16 by npigeon           #+#    #+#             */
/*   Updated: 2024/09/08 15:19:08 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_mem_and_cmd
{
	long int		cmd;
	t_memory_table	*mem;
}	t_mem_and_cmd;

typedef struct s_alias
{
	char			*name;
	char			*command;
	void			*ptr;
	struct s_alias	*next;
}	t_alias;

typedef struct s_std
{
	bool			lim;
	bool			append;
	bool			in;
	char			*name;
	bool			lim_crafted;
	int				number;
	bool			expand;
	struct s_std	*next;
}	t_std;

#endif