/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/01 14:32:45 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_lex_quote(char *str, int *i, int *j, int *opened)
{
	*opened = quote_is_goat(str[(*i)++]);
	(*j)++;
	while (*opened != 0 && str[*i])
	{
		if (quote_is_goat(str[*i]) == *opened)
		{
			*opened = 0;
			(*i)++;
			(*j)++;
			break ;
		}
		(*j)++;
		(*i)++;
	}
}

static void	handle_lex_word(char *str, int *i, int *j, int *opened)
{
	while ((str[*i] != '\'') && (str[*i] != '\"') && (str[*i] != ' ')
		&& (is_token(str, *i) == FALSE) && *opened == 0 && str[*i])
	{
		(*j)++;
		(*i)++;
	}
}

static void	lex_str(t_lex **lex, char *str)
{
	int	i;
	int	j;
	int	opened;

	i = 0;
	opened = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		j = 0;
		if ((str[i] == '\'') || (str[i] == '\"'))
			handle_lex_quote(str, &i, &j, &opened);
		else
			handle_lex_word(str, &i, &j, &opened);
		if (j != 0)
			store_new_word(lex, str, i, j);
		if (is_token(str, i) != FALSE)
			(store_new_token(lex, is_token(str, i)), i++);
		if (is_token(str, i - 1) == D_GREATER
			|| is_token(str, i - 1) == D_LOWER)
			i++;
	}
}

t_lex	*lexer(char *str)
{
	t_lex	*lex;

	lex = NULL;
	if (quote_checker(str) == FALSE)
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
	lex_str(&lex, str);
	return (lex);
}
