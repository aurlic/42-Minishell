/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:24 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/22 11:30:21 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"
# include "../srcs/libft/includes/libft.h"

# define PROMPT "\001\x1b[38;2;153;204;255m\x1b[1m\002[Jeanmi-Shell] 🫂 > \
\001\x1b[0m\002"
# define PROMPT_X "\001\x1b[1;38;5;205m\x1b[1m\002[Jacquie&Minishell] 🍆 > \
\001\x1b[0m\002"
# define PROMPT_K "\001\x1b[1;38;5;82m\x1b[1m\002[Kiwi-Shell] 🥝 > \
\001\x1b[0m\002"
# define PROMPT_D "\001\x1b[1;38;5;165m\x1b[1m\002[Shell-line Dion] 🎤 > \
\001\x1b[0m\002"
# define PROMPT_J "\001\e[0;107m\002\001\x1b[1;30m\x1b[1m\002[Minishell \
\001\e[0m\002Jackson] 🕺 > "
# define PROMPT_R "\001\x1b[1;38;5;94m\x1b[1m\002[Romani-Shell] 🦔 > \
\001\x1b[0m\002"

# define PIPE 1001
# define LOWER 1002
# define D_LOWER 1003
# define GREATER 1004
# define D_GREATER 1005

typedef struct s_env
{
	int				index;
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_path
{
	char			*pwd;
	char			*oldpwd;
}					t_path;

#endif