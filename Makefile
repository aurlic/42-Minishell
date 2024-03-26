# **************************************************************************** #
#                                    PROGRAM                                   #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #
#                                     UTILS                                    #
# **************************************************************************** #

CC			:=	cc
CFLAGS		:=	-g3 -Wall -Wextra -Werror
DEP_FLAGS	:=	-MMD -MP
LDFLAGS		:=	-lreadline
RM			:=	rm -rf

# **************************************************************************** #
#                                  DIRECTORIES                                 #
# **************************************************************************** #

SRCS_DIR 	:=	srcs
INCLD_DIR 	:=	includes
OBJS_DIR 	:=	objs
BUILTIN_DIR	:=	builtins
ENV_DIR		:=	env
EXEC_DIR	:=	exec
EXIT_DIR	:=	exit_free
LEXER_DIR	:=	lexer
LIBFT_DIR	:=	libft
MAIN_DIR	:=	main
PARSER_DIR	:=	parser
LIBFT_PATH	:=	srcs/libft

# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #

NEW			:=	\r\033[K
DEFAULT		:=	\033[0m
BLACK		:=	\033[0;30m
WHITE		:=	\033[0;37m
RED			:=	\033[0;31m
NEON_RED	:=	\033[38;5;196m
GREEN		:=	\033[0;32m
U_GREEN		:=	\033[4;32m
NEON_GREEN	:=	\033[38;5;82m
YELLOW		:=	\033[0;33m
BLUE		:=	\033[0;34m
PURPLE		:=	\033[0;35m
CYAN		:=	\033[0;36m
BOLD		:=	\033[1m
ITALIC		:=	\033[3m

# **************************************************************************** #
#                                    SOURCES                                   #
# **************************************************************************** #

# INCLUDES #
define	INC	:=
				$(INCLD_DIR)/
				$(LIBFT_DIR)/$(INCLD_DIR)/
endef
INCLUDES	:=	$(strip $(INC))
INCLD_FLAG	:=	$(addprefix -I , $(INCLUDES))

# LIBFT#
LIBFT		:=	$(SRCS_DIR)/$(LIBFT_DIR)/libft.a
define	LIB	:=
				$(LIBFT)
				$(LDFLAGS)
endef
LIB			:=	$(strip $(LIB))

# SOURCES #
define	SRC	:=	
				$(addprefix $(BUILTIN_DIR)/, \
					builtins.c \
					builtins_utils.c \
					cd.c \
					echo.c \
					env.c \
					exit.c \
					pwd.c \
					unset.c \
					export.c \
					export_utils.c \
					export_utils2.c \
				)
				$(addprefix $(ENV_DIR)/, \
					get_env.c \
					no_env.c \
				)
				$(addprefix $(EXEC_DIR)/, \
					exec_cmds.c \
					exec_cmds_utils.c \
					exec.c \
					here_doc.c \
					manage_fds.c \
					manage_redirs.c \
				)
				$(addprefix $(EXIT_DIR)/, \
					exit_shell.c \
					free_shell.c \
				)
				$(addprefix $(LEXER_DIR)/, \
					lexer_utils.c \
					lexer.c \
					store_token_words.c \
				)
				$(addprefix $(MAIN_DIR)/, \
					init.c \
					main.c \
					prompt.c \
					signals.c \
				)
				$(addprefix $(PARSER_DIR)/, \
					dollar_handler.c \
					handle_command.c \
					handle_redirections.c \
					parser_syntax.c \
					parser_utils.c \
					parser.c \
				)
endef
SRC			:=	$(strip $(SRC))

OBJS 		:= $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
DEPS		:= $(patsubst %.c,$(OBJS_DIR)/%.d,$(SRC))


# **************************************************************************** #
#                                     RULES                                    #
# **************************************************************************** #

all:	$(NAME)

$(LIBFT):
	@printf "$(NEW)[libft 📖] $(U_GREEN)Building libft: $<$(DEFAULT)\n"
	@make -C $(LIBFT_PATH)
	@printf "\n"

$(NAME): $(LIBFT) $(OBJS)
	@printf "\r\033[K[Jeanmi-Shell 🫂] \033[4;32mBuilding Jeanmi-Shell: $<\033[0m"
	@$(CC) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@printf "\r\033[K[Jeanmi-Shell 🫂] \033[0;32mDone!\033[0m\n"

-include $(DEPS)
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@printf "$(NEW)[Jeanmi-Shell 🫂] $(U_GREEN)Building:$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(BUILTIN_DIR)
	@mkdir -p $(OBJS_DIR)/$(ENV_DIR)
	@mkdir -p $(OBJS_DIR)/$(EXEC_DIR)
	@mkdir -p $(OBJS_DIR)/$(EXIT_DIR)
	@mkdir -p $(OBJS_DIR)/$(LEXER_DIR)
	@mkdir -p $(OBJS_DIR)/$(MAIN_DIR)
	@mkdir -p $(OBJS_DIR)/$(PARSER_DIR)
	@$(CC) $(DEP_FLAGS) $(CFLAGS) $(INCLD_FLAG) -c $< -o $@

clean:
	@printf "[Jeanmi-Shell 🫂] $(RED)Cleaning $(LIBFT_PATH)$(DEFAULT)\n"
	@make clean -sC $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[Jeanmi-Shell 🫂] $(RED)Cleaning .o$(DEFAULT)\n"
	@$(RM) $(OBJS_DIR)
	@printf "[Jeanmi-Shell 🫂] $(RED)Cleaned objects!$(DEFAULT)\n"

fclean: clean
	@printf "[Jeanmi-Shell 🫂] \033[0;31mDeleting Jeanmi-Shell executable\033[0m\n"
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_PATH) > /dev/null 2>&1
	@printf "[Jeanmi-Shell 🫂] \033[1;32mDone\033[0m\n\n"

re: fclean all

.PHONY: all clean fclean re