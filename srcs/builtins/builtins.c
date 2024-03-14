/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:46 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/14 11:24:52 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
