/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:39 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/29 11:53:36 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser_subprocess(t_lex *tmp_lex, t_lex *cmd_start, t_cmds **cmds)
{
	*cmds = process_command(tmp_lex, cmd_start, *cmds);
	(*cmds)->next = malloc(sizeof(t_cmds));
	if (!(*cmds)->next)
		exit_shell("parser_malloc");
	*cmds = (*cmds)->next;
}

void	expand_dollar(t_shell *shell, int i, int j)
{
	int	var_len;
	t_env *tmp;

	var_len = 0;
	tmp = shell->env;
	while (shell->cmds->tab[i][++j] == '_' || ft_isalnum(shell->cmds->tab[i][j]))
		var_len++;
	if (var_len != 0)
	{
		while (tmp)
		{
			if (!ft_strncmp(tmp->key, (shell->cmds->tab[i] + j - var_len), var_len))
				ft_printf("this variable exists\n");
			tmp = tmp->next;
		}
	}
}

void	parse_cmds_tab(t_shell *shell)
{
	int		i;
	int		j;
	t_cmds *tmp;

	i = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		while (tmp->tab[i])
		{
			j = 0;
			while (tmp->tab[i][j])
			{
				if (tmp->tab[i][j] == '$')
					expand_dollar(shell, i, j);
				j++;
			}
			i++;
		}
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
		exit_shell("parser_malloc");
	tmp_lex = lex;
	cmd_start = lex;
	cmds_head = cmds;
	while (tmp_lex)
	{
		if (tmp_lex->token == PIPE)
			(parser_subprocess(tmp_lex, cmd_start, &cmds), cmd_start = tmp_lex);
		tmp_lex = tmp_lex->next;
	}
	cmds = process_command(tmp_lex, cmd_start, cmds);
	// cmds = cmds_head;
	shell->cmds = cmds_head;
	parse_cmds_tab(shell);
}
/*
PRINT

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
*/
// void	parser(t_shell *shell, t_lex *lex)
// {
// 	t_cmds	*cmds;
// 	t_cmds	*cmds_head;
// 	t_lex	*tmp_lex;
// 	t_lex	*cmd_start;

// 	(void)shell;
// 	if (check_syntax(lex) == -1)
// 		return ;
// 	cmds = malloc(sizeof(t_cmds));
// 	if (!cmds)
// 		exit_shell("parser_malloc");
// 	tmp_lex = lex;
// 	cmd_start = lex;
// 	cmds_head = cmds;
// 	while (tmp_lex)
// 	{
// 		if (tmp_lex->token == PIPE)
// 		{
// 			process_and_link_command(&cmds, cmd_start, tmp_lex);
// 			cmd_start = tmp_lex;
// 		}
// 		tmp_lex = tmp_lex->next;
// 	}
// 	process_and_link_command(&cmds, cmd_start, tmp_lex);
// 	cmds = cmds_head;
// }
