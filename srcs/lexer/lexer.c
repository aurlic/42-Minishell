/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/16 10:50:37 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_check(char *str, char type, int *i, int *opened)
{
	if (str[*i] == type)
	{
		if (*opened == 0)
			*opened = -1;
		while (str[*i] && str[++(*i)] != type)
			continue ;
		if (str[*i] == type && *opened == -1)
			*opened = 0;
	}
}

int		quote_checker(char *str)
{
	int	i;
	int	opened_s;
	int	opened_d;

	i = 0;
	opened_s = 0;
	opened_d = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			open_check(str, '\'', &i, &opened_s);
		else if (str[i] == '\"')
			open_check(str, '\"', &i, &opened_d);
		i++;
	}
	if (opened_d || opened_s)
		return (FALSE);
	return (TRUE);
}

int		is_token(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (i++, D_GREATER);
		else
			return (GEATER);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (i++, D_LOWER);
		else
			return (LOWER);
	}
	return (0);
}

// int	check_match(char *str, int i, int sep)
// {
// 	if (sep == 1)

// }

void	store_new_word(t_lex *lex, char *str, int i, int j)
{
	t_lex *new;

	new = ft_calloc(1, sizeof(t_lex));
	if (!new)
		exit_shell("lexer malloc");
	new->word = ft_strndup(str + i - j, j);
	new->token = 0;
	if (!lex->next)
	{
		lex = new;
		new->next = NULL;
	}
	else
	{
		while (lex->next)
			lex = lex->next;
		lex->next = new;
		new->next = NULL;
	}
}

void	store_new_token(t_lex *lex, int token)
{
	t_lex *new;
	new = ft_calloc(1, sizeof(t_lex));
	if (!new)
		exit_shell("lexer malloc");
	new->word = NULL;
	new->token = token;
	if (!lex->next)
	{
		lex = new;
		new->next = NULL;
	}
	else
	{
		while (lex->next)
			lex = lex->next;
		lex->next = new;
		new->next = NULL;
	}
}

void	lex_str(t_lex *lex, char *str)
{
	int	i;
	int	j;
	int	opened;

	i = 0;
	opened = 0;
	// >                      echo "coucou" | echo ""
	while (str[i])
	{
		j = 0;
		while (str[i] == ' ')
			i++;
		// if (opened != 0)
		// 	j = check_match(str, i, opened);
		while ((str[i] != '\'') &&(str[i] != '\"') && (str[i] != ' ')
			&& (is_token(str, i) == FALSE) && opened == 0 && str[i])
		{
			if (is_token(str, i) == D_LOWER || is_token(str, i) == D_GREATER)
				i++;
			i++;
			j++;
		}
		if (j != 0)
			store_new_word(lex, str, i, j);
		if (is_token(str, i) != FALSE)
			store_new_token(lex, is_token(str, i));
		else
			i++;
	}
}

void	lexer(t_shell *shell, char *str)
{
	t_lex	*lex;

	(void)shell;
	lex = ft_calloc(1, sizeof(t_lex));
	if (!lex)
		exit_shell("lexer malloc");
	if (quote_checker(str) == FALSE)
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
	lex_str(lex, str);
	// return (lex);
}
