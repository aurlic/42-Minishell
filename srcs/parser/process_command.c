/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:40:50 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/05 14:32:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	process_redir(t_lex *lex, t_lex *cmd_start, t_cmds *new_cmd)
{
	t_lex	*redir_head;
	t_lex	*redir_tmp;
	t_lex	*prev_redir;

	redir_head = NULL;
	redir_tmp = NULL;
	prev_redir = NULL;
	while (cmd_start != lex)
	{
		if (cmd_start->next && cmd_start->next->token
			&& cmd_start->next->token != PIPE)
		{
			new_redi(&redir_head, &redir_tmp, cmd_start, new_cmd);
			if (prev_redir)
				prev_redir->next = redir_tmp;
			prev_redir = redir_tmp;
		}
		else
			cmd_start = cmd_start->next;
	}
}

static int	count_size(t_lex *cmd_start, t_lex *lex)
{
	int	i;

	i = 0;
	while (cmd_start != lex)
	{
		if (cmd_start->token == PIPE)
			cmd_start = cmd_start->next;
		i++;
		cmd_start = cmd_start->next;
	}
	return (i);
}

static void	fill_cmd_tab(t_cmds *new_cmd, t_lex *cmd_start, int i)
{
	int	j;

	j = 0;
	new_cmd->tab = malloc((i + 1) * sizeof(char *));
	if (!new_cmd->tab)
		exit_shell("parser_malloc");
	if (cmd_start && cmd_start->token == PIPE)
		cmd_start = cmd_start->next;
	while (j < i)
	{
		new_cmd->tab[j] = ft_strdup(cmd_start->word);
		j++;
		cmd_start = cmd_start->next;
	}
	new_cmd->tab[j] = NULL;
}

t_cmds	*process_command(t_lex *lex, t_lex *cmd_start, t_cmds *new_cmd)
{
	t_lex	*tmp_head;
	int		i;

	tmp_head = cmd_start;
	new_cmd = init_new_cmd(new_cmd);
	process_redir(lex, cmd_start, new_cmd);
	i = count_size(cmd_start, lex);
	fill_cmd_tab(new_cmd, tmp_head, i);
	return (new_cmd);
}
