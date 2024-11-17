# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 01:11:52 by ybeaucou          #+#    #+#              #
#    Updated: 2024/03/05 11:38:46 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = server.c client.c
OBJS = $(SRCS:.c=.o)
LIBS = -L$(LIBFT_DIR) -lft
INCLUDES = -I$(LIBFT_HEADERS)

CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
MAKE_LIBFT = make -sC $(LIBFT_DIR)

############ LIBFT ##################

LIBFT_DIR = ./Libft/
LIBFT_HEADERS = $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a

#####################################

all: server client

bonus: server client

server: $(LIBFT) server.o Makefile
	cc $(CFLAGS) server.o $(LIBS) $(INCLUDES) -o server

client: $(LIBFT) client.o Makefile
	cc $(CFLAGS) client.o $(LIBS) $(INCLUDES) -o client

%.o: %.c
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(LIBFT):
	$(MAKE_LIBFT)

clean:
	$(RM) $(OBJS)
	$(MAKE_LIBFT) clean
	
fclean:
	$(RM) $(OBJS)
	$(RM) server client
	$(MAKE_LIBFT) fclean

re: fclean all

.PHONY: all bonus libft clean fclean re