/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:46:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/13 18:24:25 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->path = ft_calloc(1, sizeof(t_path));
	if (!shell->path)
		exit_shell("Minishell");
	get_env(shell, envp);
}

