/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/14 11:25:43 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_outfile(t_shell *shell, t_cmds *cmds, t_lex *lex, int fd[2])
{
	if (fd[OUT] != -2)
		close (fd[OUT]);
	if (lex->token == GREATER)
		fd[OUT] = open(lex->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd[OUT] = open(lex->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[OUT] == -1)
		(fd[OUT] = -2, error..);
}

void	open_infile(t_shell *shell, t_cmds *cmds, t_lex *lex, int *flag_fd)
{
	if(*flag_fd != -2 && *flag_fd != -3)
		close (*flag_fd);
	if (lex->token == D_LOWER)
		*flag_fd = -3;
	if(lex->token == LOWER)
		*flag_fd = open(lex->next->word, O_RDONLY);
	if (*flag_fd == -1)
		(*flag_fd = -2, error, blablabla);
}

void	check_underscore(t_shell *shell, t_cmds *cmds)
{
	t_env 	*env_tmp;
	char	*last_arg;
	int		i;

	env_tmp = shell->env;
	while (cmds->tab[i])
		i++;
	if (i == 0)
		return ;
	last_arg = cmds->tab[i - 1];
	while (env_tmp)
	{
		if (ft_strictcmp(env_tmp->key, "_") == 0)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup(last_arg);
			return ;
		}
		env_tmp = env_tmp->next;
	}
}

void	close_parent(t_fd *fds)
{
	if (fds->in != -2)
		close(fds->in);
	if (fds->out != -2)
		close(fds->out);
}

void	handle_redirections(t_shell *shell, t_cmds *cmds, int fd[2])
{
	int		flag_fd;

	fd[IN] = manage_here_doc(shell, cmds, fd);
	fd[OUT] = -2;
	flag_fd = -2;
	while (cmds->redirection)
	{
		if (cmds->redirection->token == GREATER ||
			cmds->redirection->token == D_GREATER)
			open_outfile(shell, cmds, cmds->redirection, fd);
		else
			open_infile(shell, cmds, cmds->redirection, &flag_fd);
		cmds->redirection = cmds->redirection->next;	
	}
	if (flag_fd != -3)
	{
		if (fd[IN] != -2)
			close(fd[IN]);
		fd[IN] = flag_fd;
	}
}

void	run_cmds(t_shell *shell, t_cmds *cmds)
{
	t_fd	fds;

	fds.in = -2;
	while (cmds)
	{
		check_underscore(shell, cmds);
		init_fds(&fds);
		if (cmds->next)
			if (pipe(fds.pipe) == -1)
				return (ERROR, EXIT);
		handle_redirections(shell, cmds, fds.redirection);
		set_fds(&fds);
		if (cmds->end == 1)
			close_parent(&fds);
		else if
			check_builtins(shell, cmds, );
	}
}

void	ft_exec(t_shell *shell, t_cmds *cmds)
{
	
}

void	check_builtins(t_shell *shell, t_cmds *cmds)
{
	if (ft_strictcmp(cmds->redirection->word, "echo") == 0)
		ft_echo(cmds->next);
	else if (ft_strictcmp(cmds->redirection->word, "cd") == 0)
		ft_cd(cmds->next);
	else if (ft_strictcmp(cmds->redirection->word, "pwd") == 0)
		ft_pwd();
	else if (ft_strictcmp(cmds->redirection->word, "export") == 0)
		ft_export(cmds->next);
	else if (ft_strictcmp(cmds->redirection->word, "unset") == 0)
		ft_unset(cmds->next);
	else if (ft_strictcmp(cmds->redirection->word, "env") == 0)
		ft_env(shell->env);
	else if (ft_strictcmp(cmds->redirection->word, "exit") == 0)
		ft_exit(shell);
}

void	handle_commands(char *str, t_shell *shell)
{
	t_cmds	*cmds_tmp;

	cmds_tmp = shell->cmds;
	while (cmds_tmp)
	{
		run_cmds(shell, shell->cmds);
	}
}
