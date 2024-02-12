/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/12 14:52:21 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		check_builtins(shell, cmds_tmp);
		
	}
}