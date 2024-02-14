/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:46:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/14 15:08:10 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_shlvl(t_env *curr)
{
	int	shlvl;

	shlvl = ft_atoi(curr->value);
	if (shlvl == INT_MAX)
		curr->value = ft_strdup("0");
	else
		curr->value = ft_itoa(shlvl + 1);
}
// May need to handle SHLVL with no env
void	get_shlvl(t_shell *shell)
{
	t_env	*curr;
	t_env	*last;

	curr = shell->env;
	while (curr)
	{
		if (ft_strictcmp(curr->key, "SHLVL") != 0)
		{
			fill_shlvl(curr);
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
	shell->env = NULL;
	shell->path = ft_calloc(1, sizeof(t_path));
	if (!shell->path)
		exit_shell("Minishell");
	get_env(shell, envp);
	shell->path->pwd = get_paths(shell, "PWD");
	shell->path->oldpwd = get_paths(shell, "OLDPWD");
	get_shlvl(shell);
}

