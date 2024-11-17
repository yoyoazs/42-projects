/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:50:07 by ybeaucou          #+#    #+#             */
/*   Updated: 2024/01/12 14:33:42 by ybeaucou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# define NULL_STRING "(null)"  
# define SPECIAL_FLAGS "-.0# +"
# define HEXADECIMAL "0123456789abcdef"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

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

long long int	ft_atoi(const char *nptr);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t n, size_t size);
int				ft_isalnum(int str);
int				ft_isalpha(int str);
int				ft_isascii(int str);
int				ft_isdigit(int str);
int				ft_isprint(int str);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlen(char const *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *s1, const char *s2, size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

char			*ft_itoa(long int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			**ft_split(char const *str, char charset);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);

void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void*));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

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

char			*get_new_line(char *buffer);
char			*set_new_buffer(char *left_str);
char			*get_next_line(int fd);
char			*init_buffer(int fd, char *left_str);

#endif