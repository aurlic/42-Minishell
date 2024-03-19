/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:46 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/19 18:21:24 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_before_exit(t_fd *fds)
{
	if (!(fds->pipe[IN] == UNOPENED_FD))
		close(fds->pipe[IN]);
	if (!(fds->pipe[OUT] == UNOPENED_FD))
		close(fds->pipe[OUT]);
	if (!(fds->redir[IN] == UNOPENED_FD))
		close(fds->redir[IN]);
	if (!(fds->redir[OUT] == UNOPENED_FD))
		close(fds->redir[OUT]);
	if (!(fds->out == UNOPENED_FD))
		close(fds->out);
	if (!(fds->in == UNOPENED_FD))
		close(fds->in);
}

void	builtins_fds(t_shell *shell, t_fd *fds)
{
	if (fds->in != UNOPENED_FD)
		close(fds->in);
	if (fds->out == UNOPENED_FD)
		fds->out = dup(STDOUT_FILENO);
	if (fds->out == -1)
		(close_before_exit(fds), exit_shell(shell, "dup2"));
}

void	run_builtins(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag)
{
	if (flag == 1)
		builtins_fds(shell, fds);
	if (cmds->is_builtin == ECHO)
		echo_builtin(cmds, fds->out);
	if (cmds->is_builtin == CD)
		cd_builtin(shell, cmds);
	if (cmds->is_builtin == PWD)
		pwd_builtin(shell, fds->out);
	if (cmds->is_builtin == ENV)
		env_builtin(shell, fds->out);
	if (cmds->is_builtin == EXIT)
		exit_builtin(shell, cmds, fds);
}

int	is_builtin(char *str)
{
	if (ft_strictcmp(str, "echo"))
		return (ECHO);
	if (ft_strictcmp(str, "cd"))
		return (CD);
	if (ft_strictcmp(str, "pwd"))
		return (PWD);
	if (ft_strictcmp(str, "export"))
		return (EXPORT);
	if (ft_strictcmp(str, "unset"))
		return (UNSET);
	if (ft_strictcmp(str, "env"))
		return (ENV);
	if (ft_strictcmp(str, "exit"))
		return (EXIT);
	return (0);
}
