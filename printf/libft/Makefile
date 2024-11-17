# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:16:39 by ybeaucou          #+#    #+#              #
#    Updated: 2023/11/28 12:12:08 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g -fPIC -I $(INCLUDE_DIR)
SRCS	=	$(addprefix $(SRC_DIR)/, ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
			ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
			ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c \
			ft_tolower.c ft_toupper.c ft_itoa.c ft_putchar_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			ft_striteri.c ft_split.c ft_strjoin.c ft_strmapi.c \
			ft_strtrim.c ft_substr.c ft_strnstr.c ft_lstnew.c \
			ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstclear.c ft_lstdelone.c ft_lstiter.c	ft_lstmap.c \
			ft_hexlen.c ft_ptrlen.c ft_uitoa.c ft_ulen.c)

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