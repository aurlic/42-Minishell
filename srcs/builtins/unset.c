/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:49:45 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/26 13:33:55 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_env(t_shell *shell, t_env *tmp)
{
	if (tmp == shell->env)
	{
		shell->env = tmp->next;
		tmp->next->prev = NULL;
	}
	else
	{
		tmp->prev->next = tmp->next;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
	}
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

static void	unset_sub(t_shell *shell, t_cmds *cmds)
{
	int		i;
	t_env	*tmp;
	t_env   *first;

	i = 1;
	while (cmds->tab[i])
	{
        first = shell->env;
		tmp = first;
		while (tmp)
		{
			if (ft_strictcmp(tmp->key, cmds->tab[i]) == 1)
			{
				unset_env(shell, tmp);
				break ;
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
