# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/13 19:03:26 by ybeaucou          #+#    #+#              #
#    Updated: 2024/02/07 12:43:25 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker

PUSH_SWAP_HEADER = ./push_swap_dir/includes/
PUSH_SWAP_PATH_SRC = ./push_swap_dir/src/
PUSH_SWAP_PATH_OBJ = ./push_swap_dir/obj/
PUSH_SWAP_SRC = $(addprefix $(PUSH_SWAP_PATH_SRC), push_swap.c moves/rotate.c \
					moves/reverse_rotate.c moves/swap.c sort.c moves/push.c stack.c stack2.c \
					chunk.c free.c index.c move_stack.c pos.c parse_args.c)
PUSH_SWAP_OBJS = ${PUSH_SWAP_SRC:$(PUSH_SWAP_PATH_SRC)%.c=$(PUSH_SWAP_PATH_OBJ)%.o}

CHECKER_HEADER = ./checker_dir/includes/
CHECKER_PATH_SRC = ./checker_dir/src/
CHECKER_PATH_OBJ = ./checker_dir/obj/
CHECKER_SRC = $(addprefix $(CHECKER_PATH_SRC), main.c moves/rotate.c \
					moves/reverse_rotate.c moves/swap.c moves/push.c stack.c parse_args.c \
					stack2.c free.c )
CHECKER_OBJS = ${CHECKER_SRC:$(CHECKER_PATH_SRC)%.c=$(CHECKER_PATH_OBJ)%.o}

LIBFT = ./libft/libft.a
MAKE_LIBFT = make -C ./libft

CFLAGS = -Wall -Wextra -Werror -g3 -march=native -O3 -flto -pipe
RM = rm -rf

all: $(NAME)

$(PUSH_SWAP_PATH_OBJ)%.o: $(PUSH_SWAP_PATH_SRC)%.c
	mkdir -p $(PUSH_SWAP_PATH_OBJ)
	mkdir -p $(PUSH_SWAP_PATH_OBJ)moves
	cc $(CFLAGS) -c $< -o $@ -I $(PUSH_SWAP_HEADER)

$(NAME): $(LIBFT) $(PUSH_SWAP_OBJS) 
	cc $(CFLAGS) $(PUSH_SWAP_OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE_LIBFT)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(LIBFT) $(CHECKER_OBJS)
	cc $(CFLAGS) $(CHECKER_OBJS) $(LIBFT) -o $(NAME_BONUS)

$(CHECKER_PATH_OBJ)%.o: $(CHECKER_PATH_SRC)%.c
	mkdir -p $(CHECKER_PATH_OBJ)
	mkdir -p $(CHECKER_PATH_OBJ)moves
	cc $(CFLAGS) -c $< -o $@ -I $(CHECKER_HEADER)

clean:
	$(RM) $(PUSH_SWAP_PATH_OBJ) $(CHECKER_PATH_OBJ)
	$(MAKE_LIBFT) clean

fclean:
	$(RM) $(PUSH_SWAP_PATH_OBJ) $(CHECKER_PATH_OBJ)
	$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re bonus