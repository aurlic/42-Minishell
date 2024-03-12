/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:39 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/12 15:00:18 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser_subprocess(t_shell *shell, t_lex *tmp_lex, t_lex *cmd_start, t_cmds **cmds)
{
	*cmds = process_command(shell, tmp_lex, cmd_start, *cmds);
	(*cmds)->next = malloc(sizeof(t_cmds));
	if (!(*cmds)->next)
		exit_shell(shell, "parser_malloc");
	*cmds = (*cmds)->next;
}

void	parse_cmds_tab(t_shell *shell)
{
	int		i;
	int		j;
	t_cmds	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		i = 0;
		if (is_builtin(tmp->tab[0]))
			tmp->is_builtin = 1;
		while (tmp->tab[i])
		{
			j = 0;
			while (tmp->tab[i][j])
			{
				if (tmp->tab[i][j] == '$')
					find_dollar(tmp, shell->env, i, j);
				j++;
			}
			i++;
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
	t_lex	*cmd_start;

	if (check_syntax(lex) == -1)
		return ;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_shell(shell, "parser_malloc");
	redesign_words(shell, lex);
	tmp_lex = lex;
	cmd_start = lex;
	cmds_head = cmds;
	while (tmp_lex)
	{
		if (tmp_lex->token == PIPE)
			(parser_subprocess(shell, tmp_lex, cmd_start, &cmds), cmd_start = tmp_lex);
		tmp_lex = tmp_lex->next;
	}
	// exit_shell(&shell, "LEAKS\n");
	cmds = process_command(shell, tmp_lex, cmd_start, cmds);
	cmds = cmds_head;
	shell->cmds = cmds_head;
	if (lex)
	{
		free_lex(&lex);
		ft_printf("apres free\n");
	}
	parse_cmds_tab(shell);
	// t_cmds	*tmp = shell->cmds;
	// while (tmp)
	// {
	// 	int k = 0;
	// 	while (tmp->tab[k])
	// 	{
	// 		ft_printf("tab:[%s]\n", tmp->tab[k]);
	// 		k++;
	// 	}
	// 	while (tmp->redirection)
	// 	{
	// 		ft_printf("redir-> token: [%d] | word: [%s]\n", tmp->redirection->token, tmp->redirection->word);
	// 		tmp->redirection = tmp->redirection->next ;
	// 	}
	// 	ft_printf("---\n");
	// 	tmp = tmp->next;
	// }
}

