/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:21 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/12 11:52:50 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

typedef struct s_arg
{
	char	*word;
	int		is_token;
	struct s_arg	*next;
}t_arg; 

#endif