/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:37:15 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/21 10:13:31 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char **env, t_fd *fds)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("export ", fds->out);
		ft_putstr_fd(env[i], fds->out);
		ft_putstr_fd("\n", fds->out);
		i++;
	}
}

static void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*swap;

	i = 0;
	while (env[i + 1])
	{
		j = i + 1;
		if (env[j] && (ft_strcmp(env[i], env[j]) > 0))
		{
			swap = env[i];
			env[i] = env[j];
			env[j] = swap;
			i = -1;
		}
		i++;
	}
}

static int	env_len(t_env *env)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

static char	**copy_env(t_shell *shell, int len, int i)
{
	t_env	*tmp;
	char	**env;

	tmp = shell->env;
	env = ft_calloc(len + 1, sizeof(char *));
	if (!env)
		exit_shell(shell, "env_malloc", 1);
	while (tmp)
	{
		env[++i] = ft_strdup(tmp->key);
		if (!env[i])
			(free_matrix(env), exit_shell(shell, "env_malloc", 1));
		if (tmp->value)
		{
			env[i] = ft_strjoin_free(env[i], "=\"");
			env[i] = ft_strjoin_free(env[i], tmp->value);
			env[i] = ft_strjoin_free(env[i], "\"");
			if (!env[i])
				(free_matrix(env), exit_shell(shell, "env_malloc", 1));
		}
		tmp = tmp->next;
	}
	return (env);
}

void	no_arg(t_shell *shell, t_fd *fds)
{
	char	**env;
	int		i;

	env = NULL;
	i = -1;
	env = copy_env(shell, env_len(shell->env), i);
	sort_env(env);
	print_export(env, fds);
	free_matrix(env);
}
