/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:35:19 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 18:10:23 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_redirs(t_shell *shell)
{
	t_cmds	*tmp;
	t_lex	*redirs;
	int		fd[2];

	fd[0] = UNOPENED_FD;
	fd[1] = UNOPENED_FD;
	tmp = shell->cmds;
	while (tmp)
	{
		redirs = tmp->redirection;
		while (redirs)
		{
			if (redirs->token == D_LOWER || redirs->token == LOWER)
				fd[0] = handle_input(shell, redirs, redirs->token, fd[0]);
			else if (redirs->token == D_GREATER || redirs->token == GREATER)
				fd[1] = handle_output(shell, redirs, redirs->token, fd[0]);
			if (fd[0] == -1 || fd[1] == -1)
				return ;
			redirs = redirs->next;
		}
		tmp = tmp->next;
	}
}

void	run_exec(t_shell *shell)
{
	open_redirs(shell);
}
