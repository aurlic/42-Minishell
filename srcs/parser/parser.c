/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:15:25 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 15:39:57 by traccurt         ###   ########.fr       */
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

void	parse_cmds_tab(t_shell *shell, int i, int j, int open)
{
	t_cmds	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		i = -1;
		while (tmp->tab[++i])
		{
			j = -1;
			while (tmp->tab[i][++j])
			{
				expand_checker(tmp->tab[i][j], &open);
				if (tmp->tab[i][j] == '$' && open == 0)
				{
					find_dollar(shell, tmp, i, j);
					break ;
				}
			}
		}
		if (tmp->next == NULL)
			tmp->end = 1;
		tmp = tmp->next;
	}
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
	tmp_lex = lex;
	curr = lex;
	cmds_head = cmds;
	curr = parser_sub(shell, &cmds, &tmp_lex, curr);
	cmds = create_cmd(shell, &cmds, tmp_lex, curr);
	cmds->end = 1;
	cmds = cmds_head;
	shell->cmds = cmds_head;
	parse_cmds_tab(shell, i, 0, 0);
	parse_builtins(shell);
	redesign_words(shell, shell->cmds);
	free_lex(&lex);
}
