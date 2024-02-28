/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:39 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/28 16:31:51 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(t_shell *shell, t_lex *lex)
{
	t_cmds	*cmds;
	t_cmds	*cmds_head;
	t_lex	*tmp_lex;
	t_lex	*cmd_start;

	(void)shell;
	if (check_syntax(lex) == -1)
		return ;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_shell("parser_malloc");
	tmp_lex = lex;
	cmd_start = lex;
	cmds_head = cmds;
	while (tmp_lex)
	{
		if (tmp_lex->token == PIPE)
		{
			cmds = process_command(tmp_lex, cmd_start, cmds);
			
			cmds->next = malloc(sizeof(t_cmds));
			if (!cmds)
				exit_shell("parser_malloc");
			cmds = cmds->next;
			cmd_start = tmp_lex;
		}
		tmp_lex = tmp_lex->next;
	}
	cmds = process_command(tmp_lex, cmd_start, cmds);
	cmds = cmds_head;
	while (cmds)
	{
		int	k = 0;
		while (cmds->tab[k])
		{
			ft_printf("tab[%d]: %s\n", k, cmds->tab[k]);
			k++;
		}
		t_lex	*redirection;
		redirection = cmds->redirection;
		while (redirection)
		{
			ft_printf("TOKEN: %d | WORD: %s\n", redirection->token,
				redirection->word);
			redirection = redirection->next;
		}
		cmds = cmds->next;
	}
}
