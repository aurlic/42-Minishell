/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:46:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 15:12:13 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_arg(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	int	i;

	i = 0;
	while (cmds->tab[1][i] == ' ')
			i++;
	if (cmds->tab[1][i] == '+' || cmds->tab[1][i] == '-')
		i++;
	while (ft_isdigit(cmds->tab[1][i]))
		i++;
	if (cmds->tab[1][i])
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_return = 2;
		close_all_fds(fds);
		exit_shell(shell, "exit", 1);
	}
	g_return = (ft_atoi(cmds->tab[1]) % 256);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	close_all_fds(fds);
	exit_shell(shell, "exit", 0);
}

void	exit_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	if (cmds->tab[1] && cmds->tab[2])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	if (cmds->tab[1])
		exit_arg(shell, cmds, fds);
	g_return = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	close_all_fds(fds);
	exit_shell(shell, "exit", 0);
}
