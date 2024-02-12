/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:12:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/02/12 13:42:38 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_builtins(t_shell *shell, t_cmds *cmds)
{
	if (ft_strcmp(cmds->redirection->word, "echo") == 0)
		ft_echo(cmds->next);
	else if (ft_strcmp(cmds->redirection->word, "cd") == 0)
		ft_cd(cmds->next);
	else if (ft_strcmp(cmds->redirection->word, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(cmds->redirection->word, "export") == 0)
		ft_export(cmds->next);
	else if (ft_strcmp(cmds->redirection->word, "unset") == 0)
		ft_unset(cmds->next);
	else if (ft_strcmp(cmds->redirection->word, "env") == 0)
		ft_env(shell->env);
	else if (ft_strcmp(cmds->redirection->word, "exit") == 0)
		ft_exit(shell);
	else
		ft_exec(shell);
}
