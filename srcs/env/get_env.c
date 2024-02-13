/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:41:31 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/13 13:26:37 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/env.h"
//recup valeur et cle
void	ft_get_key_value(t_env *new, char **envp, int i)
{
	int		j;
	char	*key;

	j = 0;
	key = NULL;
	while (envp && envp[i][j])
	{
		ft_strjoin()
		if (envp[i][j] == "=")
			break ;
		j++;
	}
}
//rempli chaque node new avec ses infos
void	fill_env(t_shell *shell, t_env *new, char **envp, int i)
{
	t_env	curr; //remprend la tete a chaque fois

	curr = shell->env;
	new->index = i;
	ft_get_key_value(new, envp, i);
}

void	get_env(t_shell *shell, char **envp)
{
	t_env	*new;
	int		i;

	i = -1;
	if (!envp || envp[i])
	{
		handle_no_env(shell, envp);
		return ;
	}
	while (envp && envp[i])
	{
		new = ft_calloc(1, sizeof(t_env)); //creer une nouvele node
		if (!new)
			exit_shell("get_env");
		fill_env(shell, new, envp, i); //la rempli
		i++;
	}
}