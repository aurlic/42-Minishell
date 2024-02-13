/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/13 18:23:48 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	open_outfile(t_shell *shell, t_cmds *cmds, t_lex *lex, int fd[2])
{
	if (fd[OUT] != -2)
		close (fd[OUT]);
	if (lex->is_token == GREATER)
		fd[OUT] = open(lex->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd[OUT] = open(lex->next->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd[OUT] == -1)
			(error....);
}

void	set_infile(t_shell *shell, t_cmds *cmds, t_lex *lex)
{
	if(lex->is_token == LOWER)
		variable = open(lex->next->word, O_WRONLY);
	if (variable == -1)
		(exit, blablabla);
	
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

void	handle_redirections(t_shell *shell, t_cmds *cmds, int fd[2])
{
	while (cmds->redirection)
	{
		if (cmds->redirection->is_token == GREATER ||
			cmds->redirection->is_token == D_GREATER)
			open_outfile(shell, cmds, cmds->redirection, fd);
		else
			set_infile();
		cmds->redirection = cmds->redirection->next;	
	}
}

void	run_cmds(t_shell *shell, t_cmds *cmds)
{
	t_fd	fds;

	while (cmds)
	{
		check_underscore(shell, cmds);
		// if(cmds->redirection->is_token == D_LOWER)
		// 	run_here_doc(shell, cmds, );
		ft_init_fds(&fds);
		if (cmds->next)
		{
			if (pipe(fds.pipe) == -1)
				return (ERROR, EXIT);
		}
		handle_redirections(shell, cmds, fds.redirection);
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
	else
		ft_exec(shell, cmds);
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
