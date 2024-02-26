/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/26 14:31:21 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	lex_str(t_lex **lex, char *str)
{
	int	i;
	int	j;
	int	opened;

	i = 0;
	opened = 0;
	while (str[i]) // "asd""asd"
	{
		while (str[i] && str[i] == ' ')
			i++;
		j = 0;
		if ((str[i] == '\'') || (str[i] == '\"'))
		{
			opened = quote_is_goat(str[i++]);
			j++;
			while (opened != 0 && str[i])
			{
				if (quote_is_goat(str[i]) == opened)
				{
					opened = 0;
					i++;
					j++;
					break ;
				}
				j++;
				i++;
			}
		}
		else
		{
			while ((str[i] != '\'') &&(str[i] != '\"') && (str[i] != ' ')
				&& (is_token(str, i) == FALSE) && opened == 0 && str[i])
			{
				j++;
				i++;
			}
		}
		ft_printf("i=%d, j=%d\n", i, j);
		if (j != 0)
			store_new_word(lex, str, i, j);
		if (is_token(str, i) != FALSE)
			(store_new_token(lex, is_token(str, i)), i++);
	}
}

void	lexer(t_shell *shell, char *str)
{
	t_lex	*lex;

	(void)shell;
	lex = NULL;
	// if (!lex)
	// 	exit_shell("lexer malloc");
	if (quote_checker(str) == FALSE)
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
	lex_str(&lex, str);
	t_lex *tmp;
	tmp = lex;
	while (tmp)
	{
		ft_printf("word: %s || token: %d\n", tmp->word, tmp->token);
		tmp = tmp->next;
	}
	// return (lex);
}
