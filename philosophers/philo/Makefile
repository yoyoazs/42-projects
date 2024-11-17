# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 00:32:39 by ybeaucou          #+#    #+#              #
#    Updated: 2024/09/19 10:52:16 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

PATH_SRC = ./src/
PATH_OBJ = ./objs/
OBJS = ${SRC:$(PATH_SRC)%.c=$(PATH_OBJ)%.o}
INCLUDES = -I./includes/
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

SRC =  $(addprefix $(PATH_SRC), \
		main.c \
		init.c \
		philo_func.c \
		philo_fork.c \
		utils.c \
		utils2.c \
		monitor.c \
	)

all: $(NAME)

bonus: $(NAME)

$(OBJS): ./includes/* Makefile

$(PATH_OBJ):
	mkdir -p $@

$(PATH_OBJ)%.o: $(PATH_SRC)%.c | $(PATH_OBJ)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(OBJS) ./includes/* Makefile 
	cc $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME) -lpthread

clean:
	$(RM) $(PATH_OBJ)

fclean:
	$(RM) $(PATH_OBJ)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re