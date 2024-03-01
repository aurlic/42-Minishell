/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:24 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/01 15:26:34 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"
# include "../srcs/libft/includes/libft.h"

# define PROMPT "\x1b[38;2;153;204;255m\x1b[1m[Jeanmi-Shell] 🫂  > \x1b[0m"
# define PROMPT_X "\x1b[1;38;5;205m\x1b[1m[Jacquie&Minishell] 🍆 > \x1b[0m"
# define PROMPT_K "\x1b[1;38;5;82m\x1b[1m[Kiwi-Shell] 🥝 > \x1b[0m"
# define PROMPT_D "\x1b[1;38;5;165m\x1b[1m[Shell-line Dion] 🎤 > \x1b[0m"
# define PROMPT_J "\x1b[1;30m\x1b[1m[Minishell \x1b[1;97mJackson] 🕺 > \x1b[0m"
# define PROMPT_R "\x1b[1;38;5;94m\x1b[1m[Romani-Shell] 🦔 > \x1b[0m"

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