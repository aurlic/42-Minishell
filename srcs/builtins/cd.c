/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:38:47 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/18 15:15:12 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(t_shell *shell, char *oldpwd, char *currpwd)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp)
	{
		if (ft_strictcmp(tmp->key, "OLDPWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		if (ft_strictcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(currpwd);
		}
		tmp = tmp->next;
	}
}

void	cd(t_shell *shell, t_cmds *cmds)
{
	char	*oldpwd;
	char	*currpwd;

	//check si le path a CD existe
	// si on fait juste cd on retourne au home
	if (cmds->tab[1] && cmds->tab[2])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	oldpwd = getcwd(NULL, 0);
	if (cmds->prev || cmds->next)
	{
		ft_printf("ya une cmd autour\n");
		free(oldpwd);
		return ;
	}
	if (chdir(cmds->tab[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(oldpwd);
		return ;
	}
	currpwd = getcwd(NULL, 0);
	update_env(shell, oldpwd, currpwd);
	free(oldpwd);
	free(currpwd);
}
