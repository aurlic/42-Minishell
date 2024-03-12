/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:40:50 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/12 15:52:02 by traccurt         ###   ########.fr       */
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

static void	process_redir(t_shell *shell, t_lex *lex, t_lex **cmd_start, t_cmds *new_cmd)
{
	t_lex	*redir_head;
	t_lex	*redir_tmp;
	t_lex	*prev_redir;
	t_lex	*tmp2; 

	redir_head = NULL;
	redir_tmp = NULL;
	prev_redir = NULL;
	if ((*cmd_start) && (*cmd_start)->token && (*cmd_start)->token != PIPE)
		(create_pipe_head(shell, cmd_start));
	tmp2 = (*cmd_start);
	while ((*cmd_start) && (*cmd_start) != lex)
	{
		if (((*cmd_start)->next && (*cmd_start)->next->token
			&& (*cmd_start)->next->token != PIPE))
		{
			new_redi(shell, &redir_head, &redir_tmp, cmd_start, new_cmd);
			if (prev_redir)
				prev_redir->next = redir_tmp;
			prev_redir = redir_tmp;
		}
		else
			(*cmd_start) = (*cmd_start)->next;
	}
	(*cmd_start) = tmp2;
}

static int	count_size(t_lex **cmd_start, t_lex *lex)
{
	int	i;
	t_lex *tmp;

	i = 0;
	tmp = (*cmd_start);
	while (tmp && tmp != lex)
	{
		if (tmp->token == PIPE)
			tmp = tmp->next;
		i++;
		if(tmp)
			tmp = tmp->next;
	}
	return (i);
}

static void	fill_cmd_tab(t_shell *shell, t_cmds *new_cmd, t_lex **cmd_start, int i)
{
	int	j;
	t_lex *tmp;

	tmp = (*cmd_start);
	j = 0;
	new_cmd->tab = malloc((i + 1) * sizeof(char *));
	if (!new_cmd->tab)
		exit_shell(shell, "parser_malloc");
	if (tmp && tmp->token == PIPE)
		tmp = tmp->next;
	
	while (j < i && tmp)
	{
		if (tmp->word)
			new_cmd->tab[j] = ft_strdup(tmp->word);
		else
			new_cmd->tab[j] = "ERROR";
		j++;
		tmp = tmp->next;
	}
	new_cmd->tab[j] = NULL;
}

t_cmds	*process_command(t_shell *shell, t_lex *lex, t_lex **cmd_start, t_cmds *new_cmd)
{
	int		i;

	new_cmd = init_new_cmd(new_cmd);
	process_redir(shell, lex, cmd_start, new_cmd);
	i = count_size(cmd_start, lex);
	fill_cmd_tab(shell, new_cmd, cmd_start, i);
	return (new_cmd);
}
