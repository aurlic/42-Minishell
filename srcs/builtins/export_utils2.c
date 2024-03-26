/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:46:30 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/26 14:13:28 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_exist(t_shell *shell, char *str, int delim)
{
	t_env	*tmp;
	char	*key;

	tmp = shell->env;
	key = ft_strndup(str, delim);
	while (tmp)
	{
		if (ft_strictcmp(tmp->key, key) == 1)
		{
			free(tmp->value);
			tmp->value = ft_strdup(str + delim + 1);
			free(key);
			return (0);
		}
		tmp = tmp->next;
	}
	free(key);
	return (1);
}

int	check_exist_no_delim(t_shell *shell, char *str)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strictcmp(tmp->key, str) == 1)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}