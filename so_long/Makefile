# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 15:39:49 by ybeaucou          #+#    #+#              #
#    Updated: 2024/03/27 12:30:58 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBS_DIR = ./libs/
PATH_SRC = ./root/src/
PATH_OBJ = ./root/objs/
OBJS = ${SRC:$(PATH_SRC)%.c=$(PATH_OBJ)%.o}
LIBS = -L$(MINILIBX_DIR) -lmlx -lX11 -lXext -lm -L$(LIBFT_DIR) -lft -L$(GC_DIR) -lgc
INCLUDES = -I$(MINILIBX_HEADERS) -I$(LIBFT_HEADERS) -I$(GC_HEADERS) -I./root/includes/
CFLAGS =  -g3 -march=native -O3 -flto -pipe -Wall -Wextra -Werror
RM = rm -rf

############### MINILIBX ###############

MINILIBX_URL = https://github.com/42Paris/minilibx-linux.git
MINILIBX_DIR = $(LIBS_DIR)minilibx-linux/
MINILIBX_HEADERS = $(MINILIBX_DIR)
MINILIBX = $(MINILIBX_DIR)/libmlx.a

################ LIBFT #################

LIBFT_DIR = $(LIBS_DIR)Libft/
LIBFT_HEADERS = $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a

################## GC ##################

GC_DIR = $(LIBS_DIR)gc/
GC_HEADERS = $(GC_DIR)includes/
GC = $(GC_DIR)libgc.a

########################################

SRC =  $(addprefix $(PATH_SRC), main.c movement.c gravity.c hooks.c \
		walls/wall.c walls/wall_of_2.c walls/wall_of_3.c walls/wall_of_4.c \
		game/draw.c game/info.c game/update.c \
		enemy/enemy.c enemy/init_enemy.c enemy/draw_enemy.c \
		init/other.c init/struct.c \
		parse_map/check_path.c parse_map/parse_map.c parse_map/map.c\
		player/on_item.c player/sprite.c player/update.c player/movements.c\
		utils/error.c utils/free.c utils/utils.c utils/utils2.c utils/destroy.c\
		collectable/init.c collectable/utils.c \
		sprite/sprite.c sprite/text.c \
		screen/dead.c screen/end.c screen/start.c screen/score.c\
		multithread.c )

all: $(NAME)

bonus: $(NAME)

valgrind: $(NAME)
	valgrind --fair-sched=yes --tool=helgrind --history-level=none ./so_long 1.ber

$(OBJS): $(LIBFT) $(GC) ./root/includes/* Makefile

$(PATH_OBJ):
	mkdir -p $@ $@/walls $@/game $@/enemy $@/collectable $@/init $@/parse_map $@/player $@/sprite $@/utils $@/multithread $@/screen

$(PATH_OBJ)%.o: $(PATH_SRC)%.c | $(PATH_OBJ)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(MINILIBX) $(LIBFT) $(GC) $(OBJS) ./root/includes/* Makefile 
	cc $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME) -lpthread

$(LIBFT):
	make -sC $(LIBFT_DIR)

$(GC):
	make -sC $(GC_DIR)

$(MINILIBX):
	@echo "Downloading minilibx-linux..."
	if [ ! -d $(MINILIBX_DIR) ]; then \
		git clone $(MINILIBX_URL) $(MINILIBX_DIR); \
	fi
	make -sC $(MINILIBX_DIR)

clean:
	$(RM) $(PATH_OBJ)
	make clean -sC $(LIBFT_DIR)
	make clean -sC $(GC_DIR)

fclean:
	$(RM) $(PATH_OBJ)
	$(RM) $(NAME)
	make fclean -sC $(LIBFT_DIR)
	make fclean -sC $(GC_DIR)

re: fclean all

.PHONY: all bonus clean fclean re