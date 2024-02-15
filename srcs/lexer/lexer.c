/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:30:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/15 17:29:32 by aurlic           ###   ########.fr       */
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

void	lexer(t_shell *shell, char *str)
{
	int	i;


(void)shell;
	i = 0;
	i++;
	if (quote_checker(str) == FALSE)
		write(STDERR_FILENO, ERR_QUOTE, ft_strlen(ERR_QUOTE));
	// while (1)
	// {
	// 	while(str && str[i] == ' ')
	// 		i++;
	// 	while (str && str[i] != ' ')
	// 	{
	// 		// check les TOKENS
	// 		// 
	// 	}
	// }
}


/*
int	check_quotes(char *str, int i, char quote)
{
	while (str && str[++i])
	{
		if (str[i] == quote)
			return (TRUE);
	}
	return (FALSE);
}


if (str[i] == '\'' || str[i] == '\"')
				if (check_quotes(str, i, str[i]) == FALSE)
				

*/