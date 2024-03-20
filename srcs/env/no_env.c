/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:58:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 15:04:28 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_pwd(t_shell *shell)
{
	char	*pwd;
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	pwd = getcwd(NULL, 0);
	if (!new || !pwd)
		exit_shell(shell, "env_pwd", 1);
	new->index = 1;
	new->key = ft_strdup("PWD");
	if (!new->key)
		(exit_shell(shell, "malloc failed", 1));
	new->value = ft_strdup(pwd);
	if (!new->value)
		(exit_shell(shell, "malloc failed", 1));
	new->prev = NULL;
	new->next = NULL;
	shell->env = new;
}

static void	set_shlvl(t_shell *shell)
{
	t_env	*new;
	t_env	*curr;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exit_shell(shell, "env_shlvl", 1);
	new->index = 2;
	new->key = ft_strdup("SHLVL");
	if (!new->key)
		(exit_shell(shell, "malloc failed", 1));
	new->value = ft_strdup("0");
	if (!new->value)
		(exit_shell(shell, "malloc failed", 1));
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

static void	set_underscore(t_shell *shell)
{
	t_env	*new;
	t_env	*curr;

	curr = shell->env;
	while (curr->next)
		curr = curr->next;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		exit_shell(shell, "env_underscore", 1);
	new->index = 3;
	new->key = ft_strdup("_");
	if (!new->key)
		(exit_shell(shell, "malloc failed", 1));
	new->value = ft_strdup("./minishell");
	if (!new->value)
		(exit_shell(shell, "malloc failed", 1));
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

void	handle_no_env(t_shell *shell)
{
	set_pwd(shell);
	set_shlvl(shell);
	set_underscore(shell);
}
