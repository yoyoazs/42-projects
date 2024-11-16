/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:19:42 by ybeaucou          #+#    #+#             */
/*   Updated: 2023/12/05 10:12:48 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*init_buffer(int fd, char *left_str);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, int len2);
char	*ft_strndup(const char *str);
char	*get_new_line(char *buffer);
char	*set_new_buffer(char *left_str);

#endif