/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:24:11 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/21 12:29:34 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verif_access(t_env *env, char *str)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strictcmp(tmp->key, "PWD"))
		{
			if (ft_strictcmp(tmp->value, str))
				return (1);
		}
		if (ft_strictcmp(tmp->key, "OLDPWD"))
		{
			if (ft_strictcmp(tmp->value, str))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
