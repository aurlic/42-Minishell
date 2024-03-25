/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 10:12:40 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 15:40:00 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmds	*init_new_cmd(t_cmds *cmd)
{
	cmd->tab = NULL;
	cmd->is_builtin = 0;
	cmd->pid = -2;
	cmd->end = 0;
	cmd->redirection = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

static void	fill_cmd_tab(t_shell *shell, t_cmds **cmds, t_lex *curr, int i)
{
	int	j;

	(*cmds)->tab = ft_calloc(i + 1, sizeof(char *));
	if (!(*cmds)->tab)
		exit_shell(shell, "cmd_malloc", 1);
	j = 0;
	while (curr && curr->token != PIPE)
	{
		if (curr->word && curr->skip == 0)
		{
			(*cmds)->tab[j] = ft_strdup(curr->word);
			if (!(*cmds)->tab)
				exit_shell(shell, "fill_tab_malloc", 1);
			j++;
		}
		curr = curr->next;
	}
	(*cmds)->tab[j] = NULL;
}

void	expand_checker(char c, int *open)
{
	if (quote_is_goat(c) == 1 && *open == 1)
		*open = 0;
	if (quote_is_goat(c) == 1 && *open == 0)
		*open = 1;
}

t_cmds	*create_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr)
{
	int	i;

	*cmds = init_new_cmd(*cmds);
	set_redir(shell, cmds, tmp_lex, curr);
	i = count_tab_size(tmp_lex, curr);
	fill_cmd_tab(shell, cmds, curr, i);
	return (*cmds);
}

void	new_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr)
{
	*cmds = create_cmd(shell, cmds, tmp_lex, curr);
	(*cmds)->next = malloc(sizeof(t_cmds));
	if (!(*cmds)->next)
		exit_shell(shell, "parser_malloc", 1);
	*cmds = (*cmds)->next;
}
