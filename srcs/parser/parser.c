/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:15:25 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 15:22:31 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*parser_sub(t_shell *shell, t_cmds **cmds, t_lex **tmp_lex, t_lex *curr)
{
	while ((*tmp_lex))
	{
		if ((*tmp_lex) && (*tmp_lex)->token == PIPE)
		{
			new_cmd(shell, cmds, (*tmp_lex), curr);
			(*tmp_lex) = (*tmp_lex)->next;
			curr = (*tmp_lex);
		}
		else
			(*tmp_lex) = (*tmp_lex)->next;
	}
	return (curr);
}

void	parser(t_shell *shell, t_lex *lex)
{
	t_cmds	*cmds;
	t_cmds	*cmds_head;
	t_lex	*tmp_lex;
	t_lex	*curr;
	int		i;

	i = 0;
	if (check_syntax(lex) == -1)
		return (free_lex(&lex));
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_shell(shell, "parser_malloc", 1);
	redesign_words(shell, lex);
	tmp_lex = lex;
	curr = lex;
	cmds_head = cmds;
	curr = parser_sub(shell, &cmds, &tmp_lex, curr);
	cmds = create_cmd(shell, &cmds, tmp_lex, curr);
	cmds->end = 1;
	cmds = cmds_head;
	shell->cmds = cmds_head;
	parse_cmds_tab(shell, i);
	free_lex(&lex);
}
