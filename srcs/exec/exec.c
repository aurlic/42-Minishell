/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:35:19 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 13:56:50 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_last_cmd(t_shell *shell, t_cmds *cmds)
{
	t_env	*env_tmp;
	char	*prev_cmd;

	env_tmp = shell->env;
	if (!cmds->tab)
		return ;
	if (!cmds->tab[0])
		return ;
	prev_cmd = cmds->tab[0];
	while (env_tmp)
	{
		if (ft_strictcmp(env_tmp->key, "_") == 1)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup(prev_cmd);
			if (!env_tmp->value)
				(exit_shell(shell, "malloc failed", 1));
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

static void	child_wtermsig(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_return = 130;
	}
	if (sig == 3)
	{
		write(1, "Quit: 3\n", 8);
		g_return = 131;
	}
}

void	wait_child(t_shell *shell)
{
	int		stat;
	t_cmds	*snake;

	snake = shell->cmds;
	while (snake)
	{
		if (snake->pid != -2 && snake->pid != -1)
		{
			waitpid(snake->pid, &stat, 0);
			if (WIFSIGNALED(stat))
				child_wtermsig(WTERMSIG(stat));
			else if (WIFEXITED(stat))
				g_return = WEXITSTATUS(stat);
		}
		snake = snake->next;
	}
}

void	run_exec(t_shell *shell)
{
	t_cmds	*tmp_cmd;
	t_fd	fds;

	fds.in = UNOPENED_FD;
	tmp_cmd = shell->cmds;
	tmp_cmd->prev = NULL;
	while (tmp_cmd)
	{
		(set_last_cmd(shell, tmp_cmd), init_fds(&fds));
		if (tmp_cmd->next)
			if (pipe(fds.pipe) == -1)
				exit_shell(shell, "pipe_creation", 1);
		open_redirs(shell, tmp_cmd, &fds.redir[IN], &fds.redir[OUT]);
		set_fds(&fds);
		if (tmp_cmd->is_builtin && !tmp_cmd->next && !tmp_cmd->prev)
			run_builtins(shell, tmp_cmd, &fds);
		else if (tmp_cmd->tab[0])
			execute_cmd(shell, tmp_cmd, &fds);
		if (tmp_cmd->end == 1)
			close_parent(&fds);
		if (tmp_cmd->next)
			tmp_cmd->next->prev = tmp_cmd;
		tmp_cmd = tmp_cmd->next;
	}
	(wait_child(shell), close_all_fds(&fds));
}
