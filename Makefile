# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 11:02:46 by aurlic            #+#    #+#              #
#    Updated: 2024/02/12 09:35:34 by aurlic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                     CONFIG                                   #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror -g3

LDFLAGS		=	-lreadline

# **************************************************************************** #
#                                     SOURCES                                  #
# **************************************************************************** #

LIBFT_PATH	=	./srcs/libft

LIBFT_FILE	=	libft.a

LIBFT_LIB	=	$(LIBFT_PATH)/$(LIBFT_FILE)

SRCS		=	srcs/main.c \

INCLUDES	=	includes/ \

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
