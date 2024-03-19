/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:56:50 by traccurt          #+#    #+#             */
/*   Updated: 2024/03/19 18:03:34 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_builtin(t_shell *shell, int fd_out)
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
