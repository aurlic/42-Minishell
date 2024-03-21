/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:53:19 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/20 19:15:08 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_error(char c)
{
	g_return = 1;
	ft_putstr_fd("Minishell: export: '", STDERR_FILENO);
	ft_putchar_fd(c, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	check_export_syntax(t_cmds *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds->tab[i])
	{
		j = 0;
		while (cmds->tab[i][j])
		{
			if (cmds->tab[i][0] == '=')
				return (export_error(cmds->tab[i][0]), -1);
			if (!ft_isalnum(cmds->tab[i][j]) && cmds->tab[i][j] != '='
					&& cmds->tab[i][j] != '@' && cmds->tab[i][j] != '_')
				return (export_error(cmds->tab[i][j]), -1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	set_export(t_shell *shell, char *str)
{
	int		i;
	int		delim;
	t_env	*new;

	i = 0;
	delim = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		exit_shell(shell, "export_new_env", 1);
	while (str[i])
	{
		if (str[i] == '=')
			delim = i;
		i++;
	}
	new->key = ft_calloc(delim + 1, sizeof(char));
	if (!new->key)
		exit_shell(shell, "export_new_key", 1);
	if (delim != 0)
	{
		ft_strncpy(new->key, str, delim);
		new->value = ft_calloc((i - delim + 1), sizeof(char));
		if (!new->value)
			exit_shell(shell, "export_new_value", 1);
		if (i > delim)		
			ft_strncpy(new->value, str + delim + 1, i - delim);
		else
		{
			new->value = ft_strdup("");
			if (!new->value)
				exit_shell(shell, "export_new_value", 1);
		}
	}
	else
	{
		ft_strncpy(new->key, str, delim);
		new->value = ft_strdup("");
	}
	new->next = shell->env;
	shell->env->prev = new;
	shell->env = new;
}

void	export_builtin(t_shell *shell, t_cmds *cmds, t_fd *fds)
{
	int	i;

	if (!cmds->tab[1])
	{
		no_arg(shell, fds);
		g_return = 0;
		return ;
	}
	else if (check_export_syntax(cmds) == -1)
		return ;
	else
	{
		i = 1;
		while (cmds->tab[i] && cmds->tab[i][0])
		{
			set_export(shell, cmds->tab[i]);
			i++;
		}
		// t_env *tmp;
		// tmp = shell->env;
		// while(tmp)
		// {
		// 	ft_putstr_fd(tmp->key, fds->out);
		// 	ft_putstr_fd("=", fds->out);
		// 	ft_putstr_fd(tmp->value, fds->out);
		// 	ft_putstr_fd("\n", fds->out);
		// 	tmp = tmp->next;
		// }
	}
	g_return = 0;
}
