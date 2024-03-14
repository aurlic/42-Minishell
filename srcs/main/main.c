/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 10:06:44 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_return = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;
	t_lex	*lex;
	char	*str;

	(void)av;
	if (ac != 1)
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	while (1)
	{
		handle_signals(0);
		str = read_prompt(&shell);
		lex = lexer(&shell, str);
		if (g_return == 2)
			free_lex(&lex);
		else
		{
			parser(&shell, lex);
		// if (shell.cmds)
		// 	run_exec(shell.cmds);
		}
		free_before_new_loop(&shell);
		if (str)
			free(str);
	}
	exit(EXIT_SUCCESS);
}
