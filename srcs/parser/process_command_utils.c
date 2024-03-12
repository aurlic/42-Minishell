/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:32:15 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/12 15:31:23 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_nodes(t_shell *shell, t_lex *cmd_start)
{
	t_lex	*tmp;

	(void)shell;
	tmp = NULL;
	if (cmd_start->next->next->next)
		tmp = cmd_start->next->next->next;
	if (cmd_start->next->next)
	{
		if (cmd_start->next->next->word)
			free(cmd_start->next->next->word);
		free(cmd_start->next->next);
		cmd_start->next->next = NULL;
	}
	if (cmd_start->next)
	{
		if (cmd_start->next->word)
			free(cmd_start->next->word);
		free(cmd_start->next);
		cmd_start->next = NULL;
	}
	if (tmp)
		cmd_start->next = tmp;
}

void	new_redi(t_shell *shell, t_lex **head, t_lex **tmp, t_lex **cmd_start, t_cmds *new_cmd)
{
	if (!*head)
	{
		*head = ft_calloc(1, sizeof(t_lex));
		if (!*head)
			exit_shell(shell, "command_malloc");
		new_cmd->redirection = *head;
		*tmp = *head;
	}
	else
	{
		(*tmp)->next = ft_calloc(1, sizeof(t_lex));
		if (!(*tmp)->next)
			exit_shell(shell, "command_malloc");
		*tmp = (*tmp)->next;
	}
	(*tmp)->word = ft_strdup((*cmd_start)->next->next->word);
	(*tmp)->token = (*cmd_start)->next->token;
	join_nodes(shell, (*cmd_start));
}

void	create_pipe_head(t_shell *shell, t_lex **cmd_start)
{
	t_lex *new;

	new = malloc(sizeof(t_lex));
	if (!new)
		exit_shell(shell, "malloc");
	new->token = PIPE;
    new->word = NULL;
    new->next = (*cmd_start);
	(*cmd_start) = new;
}
