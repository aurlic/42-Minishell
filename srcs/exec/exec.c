/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:35:19 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/18 15:10:59 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_last_cmd(t_shell *shell, t_cmds *cmds)
{
	t_env 	*env_tmp;
	char	*prev_cmd;

	env_tmp = shell->env;
	if (!cmds->tab)
		return ;
	if (!cmds->tab[0])
		return ;
	prev_cmd = cmds->tab[0];
	while (env_tmp)
	{
		if (ft_strictcmp(env_tmp->key, "_") == 0)
		{
			free(env_tmp->value);

			env_tmp->value = ft_strdup(prev_cmd);
			return ;
		}
		env_tmp = env_tmp->next;
	}
}

void	close_parent(t_fd *fds)
{
	if (fds->in != UNOPENED_FD)
		close(fds->in);
	if (fds->out != UNOPENED_FD)
		close(fds->out);
}

void	run_exec(t_shell *shell)
{
	t_cmds	*tmp_cmd;
	t_fd	fds;

	fds.in = UNOPENED_FD;
	tmp_cmd = shell->cmds;
	while (tmp_cmd)
	{
		set_last_cmd(shell, tmp_cmd);
		init_fds(&fds);
		if (tmp_cmd->next)
			if (pipe(fds.pipe) == -1)
				exit_shell(shell, "pipe_creation");
		open_redirs(tmp_cmd, &fds.redir[IN], &fds.redir[OUT]);
		set_fds(&fds);
		if (tmp_cmd->is_builtin)
			run_builtins(shell, tmp_cmd, &fds);
		if (tmp_cmd->end == 1)
			close_parent(&fds);
		//exec_fds
		//run exec
		tmp_cmd = tmp_cmd->next;
	}
	close_before_exit(&fds);
}
