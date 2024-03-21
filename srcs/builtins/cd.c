/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:38:47 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 11:04:38 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	classic_cd(t_shell *shell, t_cmds *cmds, char *oldpwd)
{
	(void)shell;
	if (chdir(cmds->tab[1]) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(cmds->tab[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(oldpwd);
		g_return = 1;
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
		{
			homepwd = ft_strdup(env_tmp->value);
			if (!homepwd)
				(exit_shell(shell, "malloc failed", 1));
		}	
		env_tmp = env_tmp->next;
	}
	if (chdir(homepwd) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(homepwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		(free(homepwd), free(oldpwd), g_return = 1);
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
			if (!tmp->value)
				(exit_shell(shell, "malloc failed", 1));
		}
		if (ft_strictcmp(tmp->key, "PWD"))
		{
			free(tmp->value);
			tmp->value = ft_strdup(currpwd);
			if (!tmp->value)
				(exit_shell(shell, "malloc failed", 1));
		}
		tmp = tmp->next;
	}
}

void	cd_builtin(t_shell *shell, t_cmds *cmds)
{
	char	*oldpwd;
	char	*currpwd;

	if (cmds->tab[1] && cmds->tab[2])
	{
		g_return = 1;
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO));
	}
	oldpwd = getcwd(NULL, 0);
	if (!cmds->tab[1])
	{
		if (!back_to_home(shell, oldpwd))
			return ;
	}
	else if (!classic_cd(shell, cmds, oldpwd))
		return ;
	currpwd = getcwd(NULL, 0);
	update_env(shell, oldpwd, currpwd);
	g_return = 0;
	(free(oldpwd), free(currpwd));
}
