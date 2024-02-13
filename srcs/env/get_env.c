/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:41:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/13 16:59:59 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_key_value(t_env *new, char **envp, int i)
{
	int	j;
	int	delim;

	j = 0;
	delim = 0;
	while (envp[i][j])
	{
		if (!delim && envp[i][j] == '=')
			delim = j;
		j++;
	}
	new->key = ft_calloc(delim + 1, sizeof(char));
	if (!new->key)
		exit_shell("env_key");
	ft_strncpy(new->key, envp[i], delim);
	new->key[delim] = '\0';
	new->value = ft_calloc((j - delim) + 1, sizeof(char));
	if (!new->value)
		exit_shell("env_value");
	ft_strncpy(new->value, envp[i] + delim + 1, j - delim);
}

static void	fill_env(t_shell *shell, t_env *new, char **envp, int i)
{
	t_env	*curr;

	curr = shell->env;
	new->index = i;
	ft_get_key_value(new, envp, i);
	if (!curr)
	{
		new->prev = NULL;
		shell->env = new;
	}
	else
	{
		while (curr->next)
		{
			if (curr->next->prev != curr)
				curr->next->prev = curr;
			curr = curr->next;
		}
		curr->next = new;
		new->prev = curr;
	}
}

void	get_env(t_shell *shell, char **envp)
{
	t_env	*new;
	int		i;

	i = 0;
	if (!envp || !envp[i])
	{
		handle_no_env(shell, envp);
		return ;
	}
	while (envp && envp[i])
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			exit_shell("get_env");
		fill_env(shell, new, envp, i);
		i++;
	}
}
