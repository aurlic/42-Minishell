/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:49:45 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 13:32:18 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_env(t_shell *shell, char *var)
{
	t_env 	*tmp;

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

void	unset_builtin(t_shell *shell, t_cmds *cmds)
{
	int		i;
	t_env	*tmp;

	i = 1;
	if (!cmds->tab[1])
	{
		g_return = 1;
		return ;
	}
	while (cmds->tab[i])
	{
		tmp = shell->env;
		while (tmp)
		{
			if (ft_strictcmp(tmp->key, cmds->tab[i]) == 1)
				unset_env(shell, cmds->tab[i]);
			tmp = tmp->next;
		}
		i++;
	}
	g_return = 0;
}
