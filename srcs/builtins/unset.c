/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:49:45 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 11:04:38 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_shell *shell, char *var)
{
	t_env	*tmp;

	tmp = shell->env;
	while (ft_strictcmp(tmp->key, var) == 0)
		tmp = tmp->next;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp->key);
	free(tmp->value);
	tmp->prev = NULL;
	tmp->next = NULL;
	free(tmp);
}

static void	unset_sub(t_shell *shell, t_cmds *cmds)
{
	int		i;
	t_env	*tmp;
	t_env	*next;

	i = 1;
	while (cmds->tab[i])
	{
		tmp = shell->env;
		while (tmp)
		{
			if (ft_strictcmp(tmp->key, cmds->tab[i]) == 1)
			{
				next = tmp->next;
				unset_env(shell, cmds->tab[i]);
				tmp = next;
			}
			else
			tmp = tmp->next;
		}
		i++;
	}
}

void	unset_builtin(t_shell *shell, t_cmds *cmds)
{
	if (!cmds->tab[1])
	{
		g_return = 1;
		return ;
	}
	else
		unset_sub(shell, cmds);
	g_return = 0;
}
