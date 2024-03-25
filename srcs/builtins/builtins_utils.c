/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:40:39 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/25 15:44:45 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int	is_builtin(char *str)
{
	if (ft_strictcmp(str, "echo"))
		return (ECHO);
	if (ft_strictcmp(str, "cd"))
		return (CD);
	if (ft_strictcmp(str, "pwd"))
		return (PWD);
	if (ft_strictcmp(str, "export"))
		return (EXPORT);
	if (ft_strictcmp(str, "unset"))
		return (UNSET);
	if (ft_strictcmp(str, "env"))
		return (ENV);
	if (ft_strictcmp(str, "exit"))
		return (EXIT);
	return (0);
}
