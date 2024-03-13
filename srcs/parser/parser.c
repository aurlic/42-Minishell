/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:15:25 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/13 19:20:35 by aurlic           ###   ########.fr       */
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

int	count_tab_size(t_lex *tmp_lex, t_lex *curr)
{
	int	i;

	i = 0;
	while (curr != tmp_lex)
	{
		if (curr->skip == 0)
			i++;
		curr = curr->next;
	}
	return (i);
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

void	fill_cmd_tab(t_shell *shell, t_cmds **cmds, t_lex *curr, int i)
{
	int	j;

	(*cmds)->tab = ft_calloc(i + 1, sizeof(char *));
	if (!(*cmds)->tab)
		exit_shell(shell, "cmd_malloc");
	j = 0;
	while (curr && curr->token != PIPE)
	{
		if (curr->word && curr->skip == 0)
		{
			(*cmds)->tab[j] = ft_strdup(curr->word);
			if (!(*cmds)->tab)
				exit_shell(shell, "fill_tab_malloc");
			j++;
		}
		curr = curr->next;
	}
	(*cmds)->tab[j] = NULL;
}

t_cmds	*create_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr)
{
	int	i;

	*cmds = init_new_cmd(*cmds);
	handle_redir(shell, cmds, tmp_lex, curr);
	i = count_tab_size(tmp_lex, curr);
	fill_cmd_tab(shell, cmds, curr, i);
	return (*cmds);
}

void	new_cmd(t_shell *shell, t_cmds **cmds, t_lex *tmp_lex, t_lex *curr)
{
	*cmds = create_cmd(shell, cmds, tmp_lex, curr);
	(*cmds)->next = malloc(sizeof(t_cmds));
	if (!(*cmds)->next)
		exit_shell(shell, "parser_malloc");
	*cmds = (*cmds)->next;
}

void	parser(t_shell *shell, t_lex *lex)
{
	t_cmds	*cmds; // Will contain one command in each node (sep by '|')
	t_cmds	*cmds_head;
	t_lex	*tmp_lex; // Used to move on lex list
	t_lex	*curr; // Contains the start position of each new cmd

	if (check_syntax(lex) == -1)
			return ;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		exit_shell(shell, "parser_malloc");
	redesign_words(shell, lex); // Removes quotes
	tmp_lex = lex; // Used to keep head on lex
	curr = lex;
	cmds_head = cmds;
	while (tmp_lex)
	{
		if (tmp_lex && tmp_lex->token == PIPE)
		{
			new_cmd(shell, &cmds, tmp_lex, curr);
			tmp_lex = tmp_lex->next;
			curr = tmp_lex;
		}
		else
			tmp_lex = tmp_lex->next;
	}
	cmds = create_cmd(shell, &cmds, tmp_lex, curr);
	cmds = cmds_head;
	shell->cmds = cmds_head;
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

	// while (cmds)
	// {
	// 	ft_printf("1 cmd\n");
	// 	while (cmds->redirection)
	// 	{
	// 		ft_printf("w:[%s] t:[%d] s:[%d]\n", cmds->redirection->word, cmds->redirection->token, cmds->redirection->skip);
	// 		cmds->redirection = cmds->redirection->next;
	// 	}
	// 	cmds = cmds->next;
	// }
	free_lex(&lex);
}
