/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:24:11 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/21 15:31:09 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_directory(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	ft_putstr_fd(cmds->tab[0], STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	close_all_fds(fds);
	exit_shell(shell, "void", 1);
}
