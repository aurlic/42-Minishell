/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/12 17:39:29 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	handle_redirections(t_shell *shell, t_cmds *cmds, int *fd)
{
	
}

void	run_others_cmds(t_shell *shell, t_cmds *cmds)
{
	t_fd	fds;

	while (cmds)
	{
		check_underscore(shell, cmds);
		ft_init_fds(&fds);
		if (cmds->next)
		{
			if (pipe(fds.pipe) == -1)
				return (ERROR, EXIT);
		}
		
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
		(check_builtins(shell, cmds_tmp), cmds_tmp = cmds_tmp->next);
	run_others_cmds(shell, shell->cmds);
}