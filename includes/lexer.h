/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:21 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/16 10:37:59 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../srcs/libft/includes/libft.h"
# include "../srcs/libft/includes/ft_printf.h"
# include "../srcs/libft/includes/get_next_line.h"

# define TRUE 0
# define FALSE -1
# define ERR_QUOTE "Error: unclosed quote\n"

typedef struct s_lex
{
	char	*word;
	int		token;
	struct s_lex	*next;
}t_lex; 

#endif