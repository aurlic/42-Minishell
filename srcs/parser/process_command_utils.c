/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:32:15 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/01 15:02:17 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	join_nodes(t_lex *cmd_start)
{
	t_lex	*tmp;

	tmp = cmd_start->next->next->next;
	cmd_start->next->next = NULL;
	free(cmd_start->next->next);
	cmd_start->next = NULL;
	free(cmd_start->next);
	cmd_start->next = tmp;
}

void	new_redi(t_lex **head, t_lex **tmp, t_lex *cmd_start, t_cmds *new_cmd)
{
	if (!*head)
	{
		*head = ft_calloc(1, sizeof(t_lex));
		if (!*head)
			exit_shell("command_malloc");
		new_cmd->redirection = *head;
		*tmp = *head;
	}
	else
	{
		(*tmp)->next = ft_calloc(1, sizeof(t_lex));
		if (!(*tmp)->next)
			exit_shell("command_malloc");
		*tmp = (*tmp)->next;
	}
	(*tmp)->word = ft_strdup(cmd_start->next->next->word);
	(*tmp)->token = cmd_start->next->token;
	join_nodes(cmd_start);
}
