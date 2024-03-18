/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 14:46:40 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/18 13:13:01 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_shell *shell, int fd_out)
{
	char	*path;

	(void)shell;
	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd: error retrieving current directory: \
// getcwd: cannot access parent directories");
	}
	else
	{
		ft_putstr_fd(path, fd_out);
		ft_putstr_fd("\n", fd_out);
		// ft_printf("%s\n", path);
		g_return = 0;
		free(path);
	}
}
