/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:13:20 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/05 16:43:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	count_commands(t_lex *lex)
// {
// 	t_lex	*tmp;
// 	int		count;

// 	tmp = lex;
// 	count = 0;
// 	while (tmp)
// 	{
// 		if (tmp->token == PIPE)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count + 1);
// }

// int	count_redir(t_lex *cmd_start, t_lex *lex)
// {
// 	t_lex	*tmp;
// 	int		count;

// 	tmp = cmd_start;
// 	count = 0;
// 	while (tmp != lex)
// 	{
// 		if (tmp->token && tmp->token != PIPE)
// 			count++;
// 		tmp = tmp->next;
// 	}
// 	return (count);
// }

int	check_syntax(t_lex *lex)
{
	t_lex	*tmp;

	tmp = lex;
	if (lex && lex->token == PIPE)
		return (token_error(lex->token), -1);
	while (tmp)
	{
		if ((tmp->token != 0 && tmp->token != PIPE)
			&& ((tmp->next == NULL) || (tmp->next->token != 0)))
			return (token_error(tmp->token), -1);
		if (tmp->token == PIPE && (!tmp->next || (tmp->next->token == PIPE)))
			return (token_error(tmp->token), -1);
		tmp = tmp->next;
	}
	return (0);
}

static char	*remove_quotes(char *str, int *i, char quote)
{
	char	*tmp;
	char	*final;
	int		j;

	tmp = ft_strndup(str, *i);
	j = *i + 1;
	if (ft_strictcmp(str, ""))
		return str;
	while (str[j] && str[j] != quote)
		j++;
	final = ft_strndup(str + *i + 1, j - *i - 1);
	final = ft_strjoin_free(tmp, final);
	*i = ft_strlen(final);
	final = ft_strjoin_free(final, str + j + 1);
	return (final);
}

void	redesign_words(t_lex *lex)
{
	t_lex	*tmp;
	int		i;

	tmp = lex;
	i = 0;
	while (tmp)
	{
		i = 0;
		if (tmp->word)
		{
			while (tmp->word[i])
			{
				if ((tmp->word[i] == '\'') || (tmp->word[i] == '\"'))
					tmp->word = remove_quotes(tmp->word, &i, tmp->word[i]);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}