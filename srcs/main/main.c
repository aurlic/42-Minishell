/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/06 11:22:11 by marvin           ###   ########.fr       */
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
		parser(&shell, lex);
		// free_before_new_loop(shell)
		if (shell.cmds)
			free_cmds(shell.cmds);
		free(str);
	}
	exit(EXIT_SUCCESS);
}
