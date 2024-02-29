/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:14:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/29 17:15:18 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_dollar(char *value, char *str, int var_len, int j)
{
	char	*result;

	result = ft_strndup(str, j - var_len);
	if (value)
		result = ft_strjoin_free(result, value);
	result = ft_strjoin_free(result, str + j);
	return (result);
}

void	find_dollar(t_cmds *cmds, t_env *env, int i, int j)
{
	int		var_len;
	t_env	*tmp;
	int		var;

	var_len = 0;
	var = 0;
	tmp = env;
	while (cmds->tab[i][++j] == '_' || ft_isalnum(cmds->tab[i][j]))
		var_len++;
	if (var_len != 0)
	{
		while (tmp)
		{
			if (!ft_strictncmp(tmp->key, (cmds->tab[i] + j - var_len), var_len))
			{
				cmds->tab[i] = expand_dollar(tmp->value, cmds->tab[i], var_len + 1, j);
				var = 1;
				break ;
			}
			tmp = tmp->next;
		}
		if (var == 0)
			cmds->tab[i] = expand_dollar(NULL, cmds->tab[i], var_len + 1, j);
	}
}
