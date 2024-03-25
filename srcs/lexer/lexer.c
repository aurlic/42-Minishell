/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 15:13:50 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_lex_quote(char *str, int *i, int *j, int *opened)
{
	*opened = quote_is_goat(str[(*i)++]);
	(*j)++;
	while (*opened != 0 && str[*i])
	{
		if (quote_is_goat(str[*i]) == *opened)
		{
			while ((*opened == quote_is_goat(str[(*i)])) && str[(*i)])
			{
				(*i)++;
				(*j)++;
			}
			*opened = 0;
			break ;
		}
		(*j)++;
		(*i)++;
	}
}

static void	handle_lex_word(char *str, int *i, int *j)
{
	int	open;

	open = 0;
	while ((str[*i] != ' ') && (is_token(str, *i) == FALSE) && str[*i])
	{
		open = quote_is_goat(str[*i]);
		if (open != 0)
		{
			(*i)++;
			(*j)++;
			while (str[*i] && open != quote_is_goat(str[*i]))
			{
				(*i)++;
				(*j)++;
			}
		}
		(*j)++;
		(*i)++;
	}
}

static void	lex_str(t_shell *shell, t_lex **lex, char *str)
{
	int	i;
	int	j;
	int	opened;

	i = 0;
	opened = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || (str[i] >= 7 && str[i] <= 13)))
			i++;
		j = 0;
		if ((str[i] == '\'') || (str[i] == '\"'))
			handle_lex_quote(str, &i, &j, &opened);
		else
			handle_lex_word(str, &i, &j);
		if (j > 0)
			store_new_word(shell, lex, str, (int [2]){i, j});
		if (is_token(str, i) != FALSE)
			(store_new_token(shell, lex, is_token(str, i)), i++);
		if (is_token(str, i - 1) == D_GREATER
			|| is_token(str, i - 1) == D_LOWER)
			i++;
	}
}

t_lex	*lexer(t_shell *shell, char *str)
{
	t_lex	*lex;

	lex = NULL;
	if (quote_checker(str) == FALSE)
	{
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
		g_return = 2;
		return (lex);
	}
	lex_str(shell, &lex, str);
	return (lex);
}
