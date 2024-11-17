# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:16:39 by ybeaucou          #+#    #+#              #
#    Updated: 2024/01/10 18:32:06 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -I $(INCLUDE_DIR)
SRCS	=	$(addprefix $(SRC_DIR)/, convert/ft_atoi.c convert/ft_itoa.c convert/ft_uitoa.c \
				ft_printf/ft_printf_bonus.c ft_printf/ft_printf_char.c ft_printf/ft_printf_flags.c \
				ft_printf/ft_printf_hex.c ft_printf/ft_printf_number.c ft_printf/ft_printf_ptr.c \
				ft_printf/ft_printf_str.c ft_printf/ft_printf_struct.c ft_printf/ft_printf_unsigned.c \
				ft_printf/ft_printf.c gnl/get_next_line.c gnl/gnl_init_buffer.c gnl/gnl_new_line.c \
				gnl/gnl_set_new_buffer.c len/ft_hexlen.c len/ft_ptrlen.c len/ft_strlen.c len/ft_ulen.c \
				list/ft_lstadd_back.c list/ft_lstadd_front.c list/ft_lstclear.c list/ft_lstdelone.c \
				list/ft_lstiter.c list/ft_lstlast.c list/ft_lstmap.c list/ft_lstnew.c list/ft_lstsize.c \
				memory/ft_bzero.c memory/ft_calloc.c memory/ft_memchr.c memory/ft_memcmp.c memory/ft_memcpy.c \
				memory/ft_memmove.c memory/ft_memset.c search/ft_strchr.c search/ft_strncmp.c search/ft_strnstr.c \
				search/ft_strrchr.c string/ft_split.c string/ft_strdup.c string/ft_strjoin.c string/ft_strlcat.c \
				string/ft_strlcpy.c string/ft_strtoupper.c string/ft_strtrim.c string/ft_substr.c string/ft_tolower.c \
				string/ft_toupper.c types/ft_isalnum.c types/ft_isalpha.c types/ft_isascii.c types/ft_isdigit.c \
				types/ft_isprint.c write/ft_putchar_fd.c write/ft_putendl_fd.c write/ft_putnbr_fd.c write/ft_putstr_fd.c \
				ft_striteri.c ft_strmapi.c)

SRC_DIR = ./src
INCLUDE_DIR = ./includes
OBJS  = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)
	
fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re