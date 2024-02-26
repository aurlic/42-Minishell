/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:14:30 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/26 15:36:59 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		env = env->next;
	}
}

void	free_path(t_path *path)
{
}

void	free_cmds(t_cmds *cmds)
{
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		free_env(shell->env);
	if (shell->path)
		free_path(shell->path);
	if (shell->cmds)
		free_cmds(shell->cmds);
}
