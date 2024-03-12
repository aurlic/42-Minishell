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

// void	free_lex(t_lex *lex)
// {
// 	t_lex	*tmp;
// 	t_lex	*next;

// 	tmp = lex;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		if (tmp->word)
// 			free(tmp->word);
// 		free(tmp);
// 		tmp = next;
// 	}
// }

// void	free_cmds(t_cmds **cmds)
// {
// 	t_cmds	*tmp;
// 	t_cmds	*next;

// 	tmp = cmds;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		if (tmp->tab)
// 			free_matrix_safe(tmp->tab);
// 		if (tmp->redirection)
// 			free_lex(tmp->redirection);
// 		free(tmp);
// 		tmp = next;
// 	}
// 	cmds = NULL;
// }

void	free_lex(t_lex **lex)
{
	t_lex	*to_free;

	if (!(*lex))
		return ;
	while (*lex)
	{
		to_free = *lex;
		*lex = (*lex)->next;
		to_free->next = NULL;
		// ft_printf("word = %s | token = %d\n", to_free->word, to_free->token);
		free(to_free->word);
		free(to_free);
	}
	*lex = NULL;
}

void	free_cmds(t_cmds  **cmds)
{
	t_cmds	*tmp;
	int		i;

	i = 0;
	while (*cmds)
	{
		if ((*cmds)->tab)
		{
			while ((*cmds)->tab[i])
				free((*cmds)->tab[i++]);
			free((*cmds)->tab);
		}
		free_lex(&((*cmds)->redirection));
		tmp = *cmds;
		*cmds = (*cmds)->next;
		free(tmp);
		i = 0;
	}
	*cmds = NULL;
}

void	free_before_new_loop(t_shell *shell)
{
	if (shell->cmds)
		free_cmds(&(shell->cmds));
	// ft_printf("-> shell->cnds: %d\n", shell->cmds->is_builtin);
}

void	free_shell(t_shell *shell)
{
	if (shell->env)
		(free_env(shell->env));
	if (shell->cmds)
		free_cmds(&(shell->cmds));
	if (shell->path)
	{
		free(shell->path->pwd);
		free(shell->path->oldpwd);
		free(shell->path);
	}
}
