/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:10:57 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 11:32:23 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

typedef struct s_cmds
{
	char			**tab;
	int				is_builtin;
	int				pid;
	int				end;
	struct s_lex	*redirection;
	struct s_cmds	*prev;
	struct s_cmds	*next;
}					t_cmds;

#endif
