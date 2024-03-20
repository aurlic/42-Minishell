/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:05:51 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 15:11:10 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	create_redir(t_shell *shell, t_cmds **cmds, t_lex *curr)
{
	t_lex	*tmp;
	t_lex	*new;

	new = ft_calloc(1, sizeof(t_lex));
	if (!new)
		exit_shell(shell, "redir_malloc", 1);
	new->token = curr->token;
	new->skip = 0;
	new->word = ft_strdup(curr->next->word);
	if (!new->word)
		exit_shell(shell, "redir_malloc", 1);
	if (!(*cmds)->redirection)
		(*cmds)->redirection = new;
	else
	{
		tmp = (*cmds)->redirection;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	set_redir(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr)
{
	while (curr && curr != tmp_lex)
	{
		if (curr->token && curr->token != PIPE && curr->skip == 0)
		{
			create_redir(shell, cmds, curr);
			curr->skip = 1;
			curr->next->skip = 1;
		}
		curr = curr->next;
	}
}
