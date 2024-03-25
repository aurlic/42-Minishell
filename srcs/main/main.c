/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/25 15:15:46 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_lex	*lex;
	char	*str;

	if (ac != 1 || av[1])
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	while (1)
	{
		handle_signals(0);
		str = read_prompt(&shell);
		lex = lexer(&shell, str);
		if (!lex)
			free_lex(&lex);
		else
		{
			parser(&shell, lex);
			if (shell.cmds)
				run_exec(&shell);
		}
		free_before_new_loop(&shell);
		if (str)
			free(str);
	}
	exit(EXIT_SUCCESS);
}
