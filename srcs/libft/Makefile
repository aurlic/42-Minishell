# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 11:34:17 by aurlic            #+#    #+#              #
#    Updated: 2024/03/22 11:42:29 by aurlic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	cc

CFLAGS	=	-g3 -Wall -Wextra -Werror

RM		=	rm -f

SRCS_LIB	=	srcs/libft/ft_atoi.c \
				srcs/libft/ft_bzero.c \
				srcs/libft/ft_calloc.c \
				srcs/libft/ft_isalnum.c \
				srcs/libft/ft_isalpha.c \
				srcs/libft/ft_isascii.c \
				srcs/libft/ft_isdigit.c \
				srcs/libft/ft_isprint.c \
				srcs/libft/ft_memchr.c \
				srcs/libft/ft_memcmp.c \
				srcs/libft/ft_memcpy.c \
				srcs/libft/ft_memmove.c \
				srcs/libft/ft_memset.c \
				srcs/libft/ft_strchr.c \
				srcs/libft/ft_strdup.c \
				srcs/libft/ft_strndup.c \
				srcs/libft/ft_strlcat.c \
				srcs/libft/ft_strlcpy.c \
				srcs/libft/ft_strlen.c \
				srcs/libft/ft_strcmp.c \
				srcs/libft/ft_strncmp.c \
				srcs/libft/ft_strictcmp.c \
				srcs/libft/ft_strictncmp.c \
				srcs/libft/ft_strncpy.c \
				srcs/libft/ft_strnstr.c \
				srcs/libft/ft_strrchr.c \
				srcs/libft/ft_tolower.c \
				srcs/libft/ft_toupper.c \
				srcs/libft/ft_substr.c \
				srcs/libft/ft_strjoin.c \
				srcs/libft/ft_strjoin_free.c \
				srcs/libft/ft_strnjoin.c \
				srcs/libft/ft_strtrim.c \
				srcs/libft/ft_split.c \
				srcs/libft/ft_itoa.c \
				srcs/libft/ft_strmapi.c \
				srcs/libft/ft_striteri.c \
				srcs/libft/ft_putchar_fd.c \
				srcs/libft/ft_putstr_fd.c \
				srcs/libft/ft_putendl_fd.c \
				srcs/libft/ft_putnbr_fd.c \
				srcs/libft/ft_lstnew.c \
				srcs/libft/ft_lstadd_front.c \
				srcs/libft/ft_lstadd_back.c \
				srcs/libft/ft_lstsize.c \
				srcs/libft/ft_lstlast.c \
				srcs/libft/ft_lstdelone.c \
				srcs/libft/ft_lstclear.c \
				srcs/libft/ft_lstiter.c \
				srcs/libft/ft_lstmap.c \
				srcs/libft/free_matrix.c \

SRCS_PRINTF	=	srcs/ft_printf/ft_printf.c \
				srcs/ft_printf/handle_specifier.c \
				srcs/ft_printf/handle_specifier2.c \

SRCS_GNL	=	srcs/get_next_line/get_next_line.c \

OBJS_LIB	=	$(SRCS_LIB:.c=.o)
OBJS_PRINTF	=	$(SRCS_PRINTF:.c=.o)
OBJS_GNL	=	$(SRCS_GNL:.c=.o)

$(NAME):	$(OBJS_LIB) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "\r\033[K[libft 📖] \033[0;32mLinking...\033[0m"
	@ar rc $(NAME) $(OBJS_LIB) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "\r\033[K[libft 📖] \033[0;32mDone!\033[0m\n"

all:		$(NAME)

%.o: %.c
	@printf "\r\033[K[libft 📖] \033[0;32mBuilding : $<\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	@$(RM) $(OBJS_LIB) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "[libft 📖] \033[0;31mCleaned .o\033[0m\n"

fclean:		clean
	@$(RM) $(NAME)
	@printf "[libft 📖] \033[1;31mCleaned lib\033[0m\n"

re:			fclean all

.PHONY:		all clean fclean re
