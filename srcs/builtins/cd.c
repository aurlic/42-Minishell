/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:38:47 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/18 16:38:49 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	classic_cd(t_shell *shell, t_cmds *cmds, char *oldpwd)
{
	if (chdir(cmds->tab[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(oldpwd);
		return (0);
	}
	return (1);
}

static int	back_to_home(t_shell *shell, char *oldpwd)
{
	char	*homepwd;
	t_env	*env_tmp;

	env_tmp = shell->env;
	while (env_tmp)
	{
		if (ft_strictcmp(env_tmp->key, "HOME"))
			homepwd = ft_strdup(env_tmp->value);
		env_tmp = env_tmp->next;
	}
	if (chdir(homepwd) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(homepwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		(free(homepwd), free(oldpwd));
		return (0);
	}
	free(homepwd);
	return (1);
}

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

	if (cmds->tab[1] && cmds->tab[2])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	oldpwd = getcwd(NULL, 0);
	if (cmds->prev || cmds->next)
	{
		free(oldpwd);
		return ;
	}
	if (!cmds->tab[1])
	{
		if (!back_to_home(shell, oldpwd))
			return;
	}
	else if (!classic_cd(shell, cmds, oldpwd))
		return ;
	currpwd = getcwd(NULL, 0);
	update_env(shell, oldpwd, currpwd);
	(free(oldpwd), free(currpwd));
}
