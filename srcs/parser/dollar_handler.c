/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:14:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 12:33:05 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Old function name : expand_dollar, had to shorten to match norme.
*/
static char	*ex_dol(char *value, char *str, int var_len, int j)
{
	char	*result;
	char	*str2;

	str2 = str;
	result = ft_strndup(str, j - var_len);
	if (value)
		result = ft_strjoin_free(result, value);
	result = ft_strjoin_free(result, str2 + j);
	free(str);
	return (result);
}

static char	*dollar_ret(char *str)
{
	char	*result;
	char	*str_tmp;

	str_tmp = str;
	result = ft_itoa(g_return);
	if (str[2])
		result = ft_strjoin_free(result, str_tmp + 2);
	free(str);
	return (result);
}

static void	dollar_sub(t_env *tmp, t_cmds **cmds, int tab_n[3])
{
	int	i;
	int	j;
	int	var;
	int	len;

	i = tab_n[0];
	j = tab_n[1];
	len = tab_n[2];
	var = 0;
	while (tmp)
	{
		if (!ft_strictncmp(tmp->key, ((*cmds)->tab[i] + j - len), len))
		{
			(*cmds)->tab[i] = ex_dol(tmp->value, (*cmds)->tab[i], len + 1, j);
			var = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (var == 0)
		(*cmds)->tab[i] = ex_dol(NULL, (*cmds)->tab[i], len + 1, j);
}

void	find_dollar(t_shell *shell, t_cmds *cmds, int i, int j)
{
	t_env	*tmp;
	int		tab_n[3];

	tmp = shell->env;
	tab_n[0] = i;
	tab_n[1] = j;
	tab_n[2] = 0;
	if (cmds->tab[tab_n[0]][0] == '$' && cmds->tab[tab_n[0]][1] == '?')
	{
		cmds->tab[tab_n[0]] = dollar_ret(cmds->tab[tab_n[0]]);
		return ;
	}
	while (cmds->tab[tab_n[0]][++tab_n[1]] == '_'
			|| ft_isalnum(cmds->tab[tab_n[0]][tab_n[1]]))
		tab_n[2]++;
	if (tab_n[2] != 0)
	{
		dollar_sub(tmp, &cmds, tab_n);
	}
}
