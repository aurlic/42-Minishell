/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:35:19 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/15 11:17:04 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_builtins(t_shell *shell, int fd_in, int fd_out)
{
	t_cmds *tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		if (shell->cmds->is_builtin == ECHO)
			echo(shell->cmds, fd_in, fd_out);
		tmp = tmp->next;
	}
}

void	run_exec(t_shell *shell)
{
	t_cmds	*tmp_cmd;
	int		fd[2];

	tmp_cmd = shell->cmds;
	fd[0] = UNOPENED_FD;
	fd[1] = UNOPENED_FD;
	while (tmp_cmd)
	{
		open_redirs(tmp_cmd, &fd[0], &fd[1]);
		run_builtins(tmp_cmd, fd[0], fd[1]);
		//run exec
		tmp_cmd = tmp_cmd->next;
	}
}
