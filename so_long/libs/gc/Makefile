# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/23 21:25:45 by ybeaucou          #+#    #+#              #
#    Updated: 2024/03/27 09:59:20 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgc.a
PATH_SRC = ./src/
PATH_OBJ = ./obj/
INCLUDES = -I./includes/ -I$(LIBFT_HEADERS)

SRC = $(addprefix $(PATH_SRC), \
	gc_exit.c \
	gc_alloc.c \
	gc_free.c \
	gc_hash.c \
	gc_initialise.c \
	gc_utils.c \
	gc_add_memory_block.c)

############ LIBFT ############
LIBFT_DIR = ../Libft/
LIBFT_HEADERS = $(LIBFT_DIR)includes/
###############################

OBJS = ${SRC:$(PATH_SRC)%.c=$(PATH_OBJ)%.o}
CFLAGS = -g3 -O3 -Wall -Wextra -Werror -fPIE
RM = rm -rf

all: $(NAME)

$(PATH_OBJ):
	mkdir -p $@

$(PATH_OBJ)%.o: $(PATH_SRC)%.c | $(PATH_OBJ)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJS) ./includes/* Makefile
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) $(PATH_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re