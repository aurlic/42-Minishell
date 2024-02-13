/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:58:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/13 18:06:20 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_pwd(t_shell *shell)
{
	char	*pwd;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	pwd = getcwd(NULL, 0);
	if (!new || !pwd)
		exit_shell("env_pwd");
	new->index = 1;
	new->key = ft_strdup("PWD");
	new->value = ft_strdup(pwd);
	new->prev = NULL;
	new->next = NULL;
}

void	set_shlvl(t_shell *shell)
{
	t_env	*new;
	t_env	*curr;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exit_shell("env_shlvl");
	new->index = 2;
	new->key = ft_strdup("SHLVL");
	new->value = ft_strdup("0");
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

void	set_underscore(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*curr;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exit_shell("env_underscore");
	new->index = 3;
	new->key = ft_strdup("_");
	new->value = ft_strdup("./minishell");
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

void	handle_no_env(t_shell *shell, char **envp)
{
	set_pwd(shell);
	set_shlvl(shell);
	set_underscore(shell, envp);
}