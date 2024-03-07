/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:02:26 by marvin            #+#    #+#             */
/*   Updated: 2024/03/06 10:02:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
}

void	free_lex(t_lex *lex)
{
	t_lex	*tmp;
	t_lex	*next;

	tmp = lex;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->word)
		{
			ft_printf(" free : %s\n", tmp->word);
			free(tmp->word);
		}
		free(tmp);
		tmp = next;
	}
}

void	free_cmds(t_cmds *cmds)
{
	t_cmds	*tmp;
	t_cmds	*next;

	tmp = cmds;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->tab)
			free_matrix_safe(tmp->tab);
		if (tmp->redirection)
			free_lex(tmp->redirection);
		free(tmp);
		tmp = next;
	}
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		(free_env(shell->env));
	if (shell->cmds)
		free_cmds(shell->cmds);
	if (shell->path)
	{
		free(shell->path->pwd);
		free(shell->path->oldpwd);
	}
}
