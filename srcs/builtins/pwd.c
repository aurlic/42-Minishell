/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:40 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 14:25:24 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_builtin(t_shell *shell, t_cmds *cmds, int fd_out)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: error retrieving current directory: \
// getcwd: cannot access parent directories");
	}
	else if (cmds->tab[1] && cmds->tab[1][0] == '-')
	{
		ft_putstr_fd("pwd: ", STDERR_FILENO);
		ft_putstr_fd(": invalid option\n", STDERR_FILENO);
		g_return = 2;
		free(path);
	}
	else
	{
		ft_putstr_fd(path, fd_out);
		ft_putstr_fd("\n", fd_out);
		g_return = 0;
		free(path);
	}
}
