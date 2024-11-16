# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:16:39 by ybeaucou          #+#    #+#              #
#    Updated: 2024/11/16 22:45:59 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INCLUDE_DIR)
SRC_DIR = ./src
INCLUDE_DIR = ./includes

#################### SOURCES ####################

CONVERT_SRCS = ft_atoi.c ft_itoa.c ft_uitoa.c
LEN_SRCS = ft_hexlen.c ft_ptrlen.c ft_strlen.c ft_ulen.c
LIST_SRCS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c \
			ft_lstnew.c ft_lstsize.c
MEMORY_SRCS = ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c \
			ft_memcpy.c ft_memmove.c ft_memset.c
SEARCH_SRCS = ft_strchr.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_strcmp.c
STRING_SRCS = ft_split.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strtoupper.c ft_strtrim.c ft_substr.c \
			ft_tolower.c ft_toupper.c ft_strcpy.c
TYPES_SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			 ft_isprint.c
WRITE_SRCS = ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			 ft_putstr_fd.c
GC_SRCS = gc_exit.c gc_free.c gc_alloc.c gc_hash.c gc_utils.c \
			gc_initialise.c gc_add_memory_block.c gc_split.c \
			gc_strdup.c gc_strjoin.c gc_gnl.c gc_itoa.c
OTHER_SRCS = ft_striteri.c ft_strmapi.c ft_rand.c

SRCS =	$(addprefix $(SRC_DIR)/len/, $(LEN_SRCS)) \
		$(addprefix $(SRC_DIR)/list/, $(LIST_SRCS)) \
		$(addprefix $(SRC_DIR)/memory/, $(MEMORY_SRCS)) \
		$(addprefix $(SRC_DIR)/search/, $(SEARCH_SRCS)) \
		$(addprefix $(SRC_DIR)/string/, $(STRING_SRCS)) \
		$(addprefix $(SRC_DIR)/types/, $(TYPES_SRCS)) \
		$(addprefix $(SRC_DIR)/write/, $(WRITE_SRCS)) \
		$(addprefix $(SRC_DIR)/gc/, $(GC_SRCS)) \
		$(addprefix $(SRC_DIR)/, $(OTHER_SRCS)) \
		$(addprefix $(SRC_DIR)/convert/, $(CONVERT_SRCS))

#################### RULES ####################

OBJS= $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	/bin/rm -f $(OBJS)
	
fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re