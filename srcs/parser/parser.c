/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:15:25 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 11:21:45 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	if (check_syntax(lex) == -1)
		return ;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_shell(shell, "parser_malloc");
	redesign_words(shell, lex);
	tmp_lex = lex;
	curr = lex;
	cmds_head = cmds;
	curr = parser_sub(shell, &cmds, &tmp_lex, curr);
	cmds = create_cmd(shell, &cmds, tmp_lex, curr);
	cmds = cmds_head;
	shell->cmds = cmds_head;
	parse_cmds_tab(shell);
	free_lex(&lex);
}
