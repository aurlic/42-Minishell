/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token_words.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:19:54 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/13 14:20:35 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	store_new_token(t_shell *shell, t_lex **lex, int token)
{
	t_lex	*new;
	t_lex	*curr;

	new = ft_calloc(1, sizeof(t_lex));
	if (!new)
		exit_shell(shell, "lexer malloc");
	new->word = NULL;
	new->token = token;
	new->skip = 0;
	if (!*lex)
	{
		*lex = new;
		new->next = NULL;
	}
	else
	{
		curr = *lex;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->next = NULL;
	}
}

void	store_new_word(t_shell *shell, t_lex **lex, char *str, int i, int j)
{
	t_lex	*new;
	t_lex	*curr;

	new = ft_calloc(1, sizeof(t_lex));
	if (!new)
		exit_shell(shell, "lexer malloc");
	new->word = ft_strndup(str + i - j, j);
	new->token = 0;
	new->skip = 0;
	if (!*lex)
	{
		*lex = new;
		new->next = NULL;
	}
	else
	{
		curr = *lex;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
		new->next = NULL;
	}
}
