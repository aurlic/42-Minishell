/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:46:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:16:06 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_shlvl(t_shell *shell, t_env *curr)
{
	int	shlvl;

	shlvl = ft_atoi(curr->value);
	if (shlvl == INT_MAX)
	{
		free(curr->value);
		curr->value = ft_strdup("0");
		if (!curr->value)
			(exit_shell(shell, "malloc failed", 1));
	}
	else
	{
		free(curr->value);
		curr->value = ft_itoa(shlvl + 1);
		if (!curr->value)
			exit_shell(shell, "shlvl", 1);
	}
}

// May need to handle SHLVL with no env
void	get_shlvl(t_shell *shell)
{
	t_env	*curr;
	t_env	*last;

	(void)last;
	curr = shell->env;
	while (curr)
	{
		if (ft_strictcmp(curr->key, "SHLVL") != 0)
		{
			fill_shlvl(shell, curr);
			break ;
		}
		if (!curr->next && curr)
			last = curr;
		curr = curr->next;
	}
}

char	*get_paths(t_shell *shell, char *key)
{
	t_env	*curr;

	curr = shell->env;
	while (curr)
	{
		if (ft_strictcmp(curr->key, key) != 0)
			break ;
		curr = curr->next;
	}
	if (!curr)
		return (NULL);
	return (curr->value);
}

void	init_shell(t_shell *shell, char **envp)
{
	char	*str;

	shell->env = NULL;
	shell->cmds = NULL;
	shell->path = ft_calloc(1, sizeof(t_path));
	if (!shell->path)
		exit_shell(shell, "Minishell", 1);
	get_env(shell, envp);
	str = get_paths(shell, "PWD");
	if (str)
	{
		shell->path->pwd = ft_strdup(str);
		if (!shell->path->pwd)
			exit_shell(shell, "init malloc", 1);
	}
	str = get_paths(shell, "OLDPWD");
	if (str)
	{
		shell->path->oldpwd = ft_strdup(str);
		if (!shell->path->oldpwd)
			exit_shell(shell, "init malloc", 1);
	}
	get_shlvl(shell);
}
