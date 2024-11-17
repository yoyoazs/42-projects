# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ybeaucou <ybeaucou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 11:43:47 by ybeaucou          #+#    #+#              #
#    Updated: 2024/09/08 15:34:47 by ybeaucou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

PATH_SRC = ./src/
PATH_OBJ = ./objs/
OBJS = ${SRC:$(PATH_SRC)%.c=$(PATH_OBJ)%.o}
INCLUDES = -I$(LIBFT_HEADERS) -I./includes/
LIBS = -L$(LIBFT_DIR) -lft
CFLAGS = -g3 -Wall -Wextra -Werror
RM = rm -rf

SRC_PARSING =	$(addprefix $(PATH_SRC)parsing/, \
				ast.c \
				command.c \
				lexer.c \
				parser.c \
				std.c \
				token.c \
				split_parse.c \
				utils.c)

SRC_READLINE =	$(addprefix $(PATH_SRC)readline/, \
				auto_completion/auto_completion.c \
				auto_completion/command_comp.c \
				auto_completion/file.c \
				auto_completion/utils_file.c \
				auto_completion/utils_cmd.c \
				add_history.c \
				buffer.c \
				char.c \
				check_input.c \
				cursor.c \
				history.c \
				init.c \
				insert_char.c \
				lenght_char.c \
				readline.c \
				sigwinch.c \
				delete_char.c \
				utils.c)

SRC_EXPANDER =	$(addprefix $(PATH_SRC)expander/, \
				dollar.c \
				dollar_quote.c \
				expander.c \
				wildcard/files.c \
				wildcard/folder.c \
				wildcard/main_wildcard.c \
				wildcard/utils.c \
				ft_fnmatch/bracket.c \
				ft_fnmatch/ft_fnmatch.c \
				ft_fnmatch/parts.c)

SRC_CUSTOM =	$(addprefix $(PATH_SRC)custom/, \
				config.c \
				cwd.c \
				prompt.c)

SRC_ERROR =	$(addprefix $(PATH_SRC)error/, \
			bracket.c \
			error.c \
			redirection.c \
			utils.c)
			

SRC_BUILTINS =	$(addprefix $(PATH_SRC)builtins/, \
				built_alias.c \
				built_alias_util.c \
				built_cd.c \
				built_echo.c \
				built_env.c \
				built_exit.c \
				built_exit_util.c \
				built_export.c \
				built_export_util.c \
				built_pwd.c \
				built_unset.c)

SRC_EXEC =	$(addprefix $(PATH_SRC)exec/, \
			buildings.c \
			gestion_errors.c \
			here_doc.c \
			messages.c \
			opening.c \
			pipex_cut_find_cmd.c \
			pipex_exec.c \
			pipex_free.c \
			pipex_utils.c \
			pipex.c \
			split.c \
			split_utils.c)

SRC_ALONE =	$(addprefix $(PATH_SRC), \
			ansii.c \
			exec_2.c \
			exec.c \
			signaux.c \
			utils.c \
			main.c)

SRC =	$(SRC_ALONE) $(SRC_BUILTINS) $(SRC_CUSTOM) $(SRC_ERROR) $(SRC_EXEC) $(SRC_EXPANDER) $(SRC_PARSING) $(SRC_READLINE)

################ LIBFT #################

LIBFT_DIR = ./Libft/
LIBFT_HEADERS = $(LIBFT_DIR)includes/
LIBFT = $(LIBFT_DIR)libft.a

########################################

all: $(NAME)

$(OBJS): ./includes/* Makefile

$(PATH_OBJ):
	mkdir -p $@ $@custom $@builtins $@parsing $@exec $@expander $@expander/ft_fnmatch $@expander/wildcard $@readline $@readline/auto_completion $@error
	
$(PATH_OBJ)%.o: $(PATH_SRC)%.c | $(PATH_OBJ)
	cc -c $(CFLAGS) $(INCLUDES) $< -o $@

$(NAME): $(LIBFT) $(OBJS) ./includes/* Makefile 
	cc $(CFLAGS) $(OBJS) $(LIBS) $(INCLUDES) -o $(NAME)

$(LIBFT):
	make -sC $(LIBFT_DIR)

clean:
	make clean -sC $(LIBFT_DIR)
	$(RM) $(PATH_OBJ)

fclean:
	make fclean -sC $(LIBFT_DIR)
	$(RM) $(PATH_OBJ)
	$(RM) $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME)
	
.PHONY: all clean fclean re