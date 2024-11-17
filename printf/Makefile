# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/17 10:27:33 by ybeaucou          #+#    #+#              #
#    Updated: 2023/12/05 13:03:44 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

MANDATORY_HEADER = ./mandatory/includes/
MANDATORY_PATH_SRC = ./mandatory/src/
MANDATORY_PATH_OBJ = ./mandatory/obj/
MANDATORY_SRC = $(addprefix $(MANDATORY_PATH_SRC), ft_printf.c ft_printf_char.c ft_printf_hexa.c ft_printf_nbr.c ft_printf_ptr.c ft_printf_str.c ft_printf_uint.c)
MANDATORY_OBJS = ${MANDATORY_SRC:$(MANDATORY_PATH_SRC)%.c=$(MANDATORY_PATH_OBJ)%.o}

BONUS_HEADER = ./bonus/includes/
BONUS_PATH_SRC = ./bonus/src/
BONUS_PATH_OBJ = ./bonus/obj/
BONUS_SRC = $(addprefix $(BONUS_PATH_SRC), ft_printf_hex.c ft_printf_number.c ft_printf_ptr.c ft_printf_unsigned.c ft_printf.c ft_printf_struct.c ft_printf_str.c ft_printf_char.c ft_printf_flags.c ft_printf_bonus.c)
BONUS_OBJS = ${BONUS_SRC:$(BONUS_PATH_SRC)%.c=$(BONUS_PATH_OBJ)%.o}

LIBFT = ./libft/libft.a
LIBFT_HEADER = ./libft/includes
MAKE_LIBFT = make -C ./libft

CFLAGS = -c -Wall -Wextra -Werror
AR = ar -rcs
RM = rm -rf

all: $(NAME)

$(MANDATORY_PATH_OBJ)%.o: $(MANDATORY_PATH_SRC)%.c
	mkdir -p $(MANDATORY_PATH_OBJ)
	cc $(CFLAGS) -c $< -o $@ -I $(MANDATORY_HEADER)

$(NAME): $(LIBFT) $(MANDATORY_OBJS) 
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(MANDATORY_OBJS)

$(LIBFT):
	$(MAKE_LIBFT)

bonus: $(LIBFT) $(BONUS_OBJS) 
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(BONUS_OBJS)

$(BONUS_PATH_OBJ)%.o: $(BONUS_PATH_SRC)%.c
	mkdir -p $(BONUS_PATH_OBJ)
	cc $(CFLAGS) -c $< -o $@ -I $(BONUS_HEADER)

clean:
	$(RM) $(MANDATORY_PATH_OBJ) $(BONUS_PATH_OBJ)
	$(MAKE_LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re