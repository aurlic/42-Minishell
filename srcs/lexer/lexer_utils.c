/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:17:12 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 09:54:13 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_token(char *str, int i)
{
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (i++, D_GREATER);
		else
			return (GREATER);
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (i++, D_LOWER);
		else
			return (LOWER);
	}
	return (FALSE);
}

int	quote_is_goat(char quote)
{
	if (quote == '\'')
		return (1);
	if (quote == '\"')
		return (2);
	else
		return (0);
}

static void	open_check(char *str, char type, int *i, int *opened)
{
	if (str[*i] == type)
	{
		if (*opened == 0)
			*opened = -1;
		while (str[*i] && str[*i + 1] && str[++(*i)] != type)
			continue ;
		if (str[*i] == type && *opened == -1)
			*opened = 0;
	}
}

int	quote_checker(char *str)
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
