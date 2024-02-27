/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:00:39 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/27 19:02:15 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_syntax(t_lex *lex)
{
	t_lex *tmp;

	tmp = lex;
	if (lex && lex->token == PIPE)
		return (token_error(lex->token));
	while (tmp)
	{
		if ((tmp->token != 0 && tmp->token != PIPE)
			&& ((tmp->next == NULL) || (tmp->next->token != 0)))
			return (token_error(tmp->token));
		if (tmp->token == PIPE && (!tmp->next || (tmp->next->token == PIPE)))
			return (token_error(tmp->token));
		tmp = tmp->next;
	}
}

int		count_commands(t_lex *lex)
{
	t_lex	*tmp;
	int		count;

	tmp = lex;
	count = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count + 1);
}

int		count_redir(t_lex *cmd_start, t_lex *lex)
{
	t_lex	*tmp;
	int		count;

	tmp = cmd_start;
	count = 0;
	while (tmp != lex)
	{
		if (tmp->token && tmp->token != PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

t_cmds	*init_new_cmd(t_cmds *cmd)
{
	cmd = ft_calloc(1, sizeof(t_cmds));
	if (!cmd)
		exit_shell("parser_malloc");
	cmd->tab = NULL;
	cmd->pid = -2;
	cmd->end = 0;
	cmd->redirection = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	join_nodes(t_lex *cmd_start)
{
	t_lex	*tmp;

	tmp = cmd_start->next->next->next;
	cmd_start->next->next = NULL;
	free(cmd_start->next->next);
	cmd_start->next = NULL;
	free(cmd_start->next);	
	cmd_start->next = tmp;
}

t_cmds	*process_command(t_lex *lex, t_lex *cmd_start)
{
	t_cmds	*new_cmd;
	t_lex	*holder;
	// t_lex	*hold_file;

	ft_printf("redir: %d\n", count_redir(cmd_start, lex));
	holder = malloc(sizeof(t_lex));
	new_cmd = NULL;
	new_cmd = init_new_cmd(new_cmd);
	while (cmd_start != lex)
	{
		if (cmd_start->next && cmd_start->next->token)
		{
			holder->token = cmd_start->next->token;
			holder->word = ft_strdup(cmd_start->next->next->word);
			join_nodes(cmd_start);
		}
		cmd_start = cmd_start->next;
	}
	// new_cmd->redirection = holder;
	return (new_cmd);
}

void	parser(t_shell *shell, t_lex *lex)
{
	t_cmds	*cmds;
	t_cmds	*cmds_head;
	t_lex	*tmp_lex;
	t_lex	*cmd_start;

	(void)shell;
	check_syntax(lex);
	cmds = ft_calloc(count_commands(lex), sizeof(t_cmds));
	if (!cmds)
		exit_shell("parser_malloc");
	tmp_lex = lex;
	cmd_start = lex;
	cmds_head = cmds;
	while (tmp_lex)
	{
		if (tmp_lex->token == PIPE)
		{
			cmds = process_command(tmp_lex, cmd_start);
			cmds = cmds->next;
			cmd_start = tmp_lex;
		}
		tmp_lex = tmp_lex->next;
	}
	cmds = process_command(tmp_lex, cmd_start);
	cmds->next = NULL;
}





// void	parser(t_shell *shell, t_lex *lex)
// {
// 	t_cmds	*cmd;
// 	t_cmds	*cmd_head;
// 	t_lex	*tmp;
// 	t_lex	*tmp2;

// 	(void)shell;
// 	check_syntax(lex);
// 	cmd_head = NULL;
// 	tmp = lex;
// 	tmp2 = lex;
// 	while (tmp)
// 	{
// 		if (tmp->token == PIPE)
// 		{
// 			cmd = process_command(tmp, tmp2);
// 			if (!cmd_head)
// 				cmd_head = cmd;
// 			cmd = cmd->next;
// 			tmp2 = tmp;
// 		}
// 		tmp = tmp->next;
// 	}
// 	cmds = 
// }

// t_cmds	*process_command(t_lex *lex, t_lex *head)
// {
// 	t_cmds	*cmd;
// 	t_lex	*token_node;
// 	t_lex	*file_node;
// 	t_lex	*tmp;

// 	cmd = init_new_cmd(cmd);
// 	tmp = head;
// 	while (head != lex)
// 	{
// 		if (head->token)
// 		{
// 			token_node = head;
// 			file_node = head->next;
// 			head->next = head->next->next;
// 		}
// 		head = head->next;
// 	}
// 	cmd->redirection = token_node;
// 	cmd->redirection->next = file_node;
// 	cmd->tab = lex_to_tab();
// 	return (cmd);
// }