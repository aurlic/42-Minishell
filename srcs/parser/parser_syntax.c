/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:13:20 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 15:42:11 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Old name: remove_quotes
*/
static char	*rmq(t_shell *shell, char *str, int *i, char quote)
{
	char	*tmp;
	char	*final;
	char	*final_tmp;
	int		j;

	tmp = ft_strndup(str, *i);
	j = *i + 1;
	if (ft_strictcmp(str, ""))
		return (str);
	while (str[j] && str[j] != quote)
		j++;
	final_tmp = ft_strndup(str + *i + 1, j - *i - 1);
	final = ft_strjoin_free(tmp, final_tmp);
	free(final_tmp);
	*i = ft_strlen(final);
	final = ft_strjoin_free(final, str + j + 1);
	if (!final)
		exit_shell(shell, "malloc", 1);
	free(str);
	return (final);
}

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

void	redesign_words(t_shell *shell, t_cmds *cmds)
{
	t_cmds	*tmp;
	int		i;
	int		j;

	tmp = cmds;
	while (tmp)
	{
		i = 0;
		while (tmp->tab[i])
		{
			j = 0;
			while (tmp->tab[i][j])
			{
				if ((tmp->tab[i][j] == '\'') || (tmp->tab[i][j] == '\"'))
					tmp->tab[i] = rmq(shell, tmp->tab[i], &j, tmp->tab[i][j]);
				else
					j++;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
