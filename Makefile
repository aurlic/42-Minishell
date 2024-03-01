# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 11:02:46 by aurlic            #+#    #+#              #
#    Updated: 2024/03/01 15:37:47 by aurlic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                     CONFIG                                   #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g3
#MAY NEED TO BE USED FOR SIGACTION -D_XOPEN_SOURCE=700

LDFLAGS		=	-lreadline

# **************************************************************************** #
#                                     SOURCES                                  #
# **************************************************************************** #

LIBFT_PATH	=	./srcs/libft

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

SRCS		=	srcs/main/main.c \
				srcs/main/init.c \
				srcs/main/prompt.c \
				srcs/main/signals.c \
				srcs/env/get_env.c \
				srcs/env/no_env.c \
				srcs/exit_free/exit_shell.c \
				srcs/lexer/lexer.c \
				srcs/lexer/store_token_words.c \
				srcs/lexer/lexer_utils.c \
				srcs/parser/parser.c \
				srcs/parser/parser_syntax.c \
				srcs/parser/process_command.c \
				srcs/parser/process_command_utils.c \
				srcs/parser/dollar_handler.c \
				srcs/builtins/builtins.c \

# INCLUDES	=	includes/ \ TO MAKE IT WORK GIVE ABSOLUTE PATH IN FILES AND INLUDE WHILE COMPILING

# **************************************************************************** #
#                                     OBJECTS                                  #
# **************************************************************************** #

OBJS		=	$(SRCS:.c=.o)

# **************************************************************************** #
#                                  MAKEFILE RULES                              #
# **************************************************************************** #

.c.o:
	@printf "\r\033[K[Jeanmi-Shell] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

lib:
	@printf "\r\033[K[libft] \033[4;32mBuilding libft: $<\033[0m\n"
	@make -C $(LIBFT_PATH)
	@printf "\n"

$(NAME): lib $(OBJS)
	@printf "\r\033[K[Jeanmi-Shell] \033[4;32mBuilding Jeanmi-Shell: $<\033[0m"
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBFT_LIB) -o $(NAME)
	@printf "\r\033[K[Jeanmi-Shell] \033[0;32mDone!\033[0m\n"

clean:
	@printf "[Jeanmi-Shell] \033[0;31mCleaning $(LIBFT_PATH)\033[0m\n"
	@make clean -sC $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[Jeanmi-Shell] \033[0;31mCleaning .o\033[0m\n"
	@rm -f $(OBJS)
	@printf "[Jeanmi-Shell] \033[0;31mCleaned objects!\033[0m\n"

fclean: clean
	@printf "[Jeanmi-Shell] \033[0;31mDeleting Jeanmi-Shell executable\033[0m\n"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[Jeanmi-Shell] \033[1;32mDone\033[0m\n\n"

re: fclean all

.PHONY: all clean fclean re
