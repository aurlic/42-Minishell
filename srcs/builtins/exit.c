/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:46:34 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:15:00 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_arg(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag)
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
		(close_all_fds(fds), g_return = 2);
		if (flag == 0)
			exit_shell(shell, "exit", 0);
		else
			exit_shell(shell, "void", 0);
	}
	(close_all_fds(fds), g_return = (ft_atoi(cmds->tab[1]) % 256));
	if (flag == 0)
		exit_shell(shell, "exit", 0);
	else
		exit_shell(shell, "void", 0);
}

void	exit_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds, int flag)
{
	if (cmds->tab[1] && cmds->tab[2])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	if (cmds->tab[1])
		exit_arg(shell, cmds, fds, flag);
	g_return = 0;
	close_all_fds(fds);
	if (flag == 0)
		exit_shell(shell, "exit", 0);
	else
		exit_shell(shell, "void", 0);
}
