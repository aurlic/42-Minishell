/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/13 18:26:43 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_signals(int action)
// {
// 	//
// }

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	// char	*str;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	// while (shell.env)
	// {
	// 	ft_printf("%s=%s\n", shell.env->key, shell.env->value);
	// 	shell.env = shell.env->next;
	// }
	// while (1)
	// {
	// 	handle_signals(0);
	// }
}
