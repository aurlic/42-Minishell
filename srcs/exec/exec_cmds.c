/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:09:40 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/21 15:39:12 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_shell *shell, t_cmds *cmds, t_fd *fds)
{	
	char	*f_path;

	f_path = run_cmds(shell, cmds, fds);
	if (!f_path)
		(close_all_fds(fds), g_return = 127, exit(1));
	if (fds->pipe[IN] != UNOPENED_FD)
		close(fds->pipe[IN]);
	if (fds->in != UNOPENED_FD)
		if (dup2(fds->in, STDIN_FILENO) == -1)
			(free(f_path), close_all_fds(fds), exit_shell(shell, "dup2", 1));
	if (fds->out != UNOPENED_FD)
		if (dup2(fds->out, STDOUT_FILENO) == -1)
			(free(f_path), close_all_fds(fds), exit_shell(shell, "dup2", 1));
	close_all_fds(fds);
	if (execve(f_path, cmds->tab, NULL) == -1)
		(free(f_path), exit_shell(shell, "execve", 1), g_return = 126);
	free(f_path);
}

void	execute_cmd(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	cmds->pid = fork();
	if (cmds->pid == -1)
		(close_all_fds(fds), exit_shell(shell, "fork", 1));
	if (cmds->pid == 0)
	{
		if (cmds->is_builtin)
		{
			run_builtins(shell, cmds, fds);
			(close_all_fds(fds), exit(1));
		}
		else
			execute_child(shell, cmds, fds);
	}
	close_parent(fds);
	fds->in = fds->pipe[0];
}

char	*ft_pathfinding(t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strictcmp(env_tmp->key, "PATH"))
			return (env_tmp->value);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

char	*chr_cmd(t_shell *shell, t_cmds *cmds, char **path, t_fd *fds)
{
	char	*full_path;
	char	*add_path;
	int		i;
	struct stat file_info;

	(void)shell;
	i = 0;
	full_path = NULL;
	if (ft_strchr(cmds->tab[0], '/') != NULL && access(cmds->tab[0],
			F_OK | X_OK) == 0)
	{
		if (stat(cmds->tab[0], &file_info) == 0)
			is_directory(shell, cmds, fds);
	}
	while (path && path[i])
	{
		add_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin_free(add_path, cmds->tab[0]);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		full_path = NULL;
		i++;
	}
	return (full_path);
}

char	*run_cmds(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	char	*full_path;
	char	**path;

	path = ft_split(ft_pathfinding(shell->env), ':');
	if (!path)
	{
		ft_putstr_fd(cmds->tab[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (NULL);
	}
	full_path = chr_cmd(shell, cmds, path, fds);
	if (!full_path)
	{
		if (path)
			free_matrix_safe(path);
		ft_putstr_fd(cmds->tab[0], STDERR_FILENO);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
		return (NULL);
	}
	else
		return (free_matrix_safe(path), full_path);
}
