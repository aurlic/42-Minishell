/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:21 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:31:42 by aurlic           ###   ########.fr       */
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
	char			*word;
	int				token;
	int				skip;
	struct s_lex	*next;
}					t_lex;

/* lexer_utils.c */
int		quote_is_goat(char quote);
int		quote_checker(char *str);
int		is_token(char *str, int i);
/* lexer.c */
t_lex	*lexer(t_shell *shell, char *str);
/* store_token_words.c */
void	store_new_token(t_shell *shell, t_lex **lex, int token);
void	store_new_word(t_shell *shell, t_lex **lex, char *str, int ij[2]);

#endif