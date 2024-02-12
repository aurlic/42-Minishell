/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:24 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/12 14:33:51 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

typedef struct	s_env
{
	int		index;
	char	*key;
	char	*value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct	s_path
{
	char	*pwd;
	char	*oldpwd;
}				t_path;

#endif