/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:25:02 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/14 11:25:02 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_option(char **tab, int *option)
{
	int	i;

	i = 1;
	while (tab[i] && ft_strictcmp(tab[i], "-n") == 1)
	{
		*option = 1;
		i++;
	}
	return (i);
}

void	echo_builtin(t_cmds *cmds, int fd_out)
{
	int		i;
	int		option;

	option = 0;
	i =	check_option(cmds->tab, &option);
	while (cmds->tab[i])
	{
		ft_putstr_fd(cmds->tab[i], fd_out);
		if (cmds->tab[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (!option)
		ft_putstr_fd("\n", fd_out);
	g_return = 0;
}
