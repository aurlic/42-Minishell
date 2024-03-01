/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:36:50 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/01 15:37:20 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *str)
{
	if (ft_strictcmp(str, "echo") || ft_strictcmp(str, "\'echo\'")
		|| ft_strictcmp(str, "\"echo\""))
		return (1);
	if (ft_strictcmp(str, "cd") || ft_strictcmp(str, "\'cd\'")
		|| ft_strictcmp(str, "\"cd\""))
		return (1);
	if (ft_strictcmp(str, "pwd") || ft_strictcmp(str, "\'pwd\'")
		|| ft_strictcmp(str, "\"pwd\""))
		return (1);
	if (ft_strictcmp(str, "export") || ft_strictcmp(str, "\'export\'")
		|| ft_strictcmp(str, "\"export\""))
		return (1);
	if (ft_strictcmp(str, "unset") || ft_strictcmp(str, "\'unset\'")
		|| ft_strictcmp(str, "\"unset\""))
		return (1);
	if (ft_strictcmp(str, "env") || ft_strictcmp(str, "\'env\'")
		|| ft_strictcmp(str, "\"env\""))
		return (1);
	if (ft_strictcmp(str, "exit") || ft_strictcmp(str, "\'exit\'")
		|| ft_strictcmp(str, "\"exit\""))
		return (1);
	return (0);
}
