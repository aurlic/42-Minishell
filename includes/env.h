/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:24 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/26 16:48:55 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

# define PASTEL_BLUE "\x1b[38;2;153;204;255m"
# define NEON_PINK "\x1b[1;38;5;205m"
# define BOLD "\x1b[1m"
# define RESET "\x1b[0m"

# define PROMPT_MESSAGE PASTEL_BLUE BOLD "[Jeanmi-Shell] 🫂  > " RESET
# define PROMPT_MESSAGE_HIDDEN NEON_PINK "[Jacquie&Minishell] 🍆 > " RESET

# define PIPE 1001
# define LOWER 1002
# define D_LOWER 1003
# define GEATER 1004
# define D_GREATER 1005


typedef struct	s_env
{
	int				index;
	char			*key;
	char			*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct	s_path
{
	char		*pwd;
	char		*oldpwd;
}				t_path;

#endif