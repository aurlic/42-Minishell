/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:56:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/18 13:11:36 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_shell *shell, int fd_out)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		ft_putstr_fd(env->key, fd_out);
		ft_putstr_fd("=", fd_out);
		ft_putstr_fd(env->value, fd_out);
		ft_putstr_fd("\n", fd_out);
		// ft_printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
