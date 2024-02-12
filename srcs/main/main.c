/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:44:58 by aurlic            #+#    #+#             */
/*   Updated: 2024/02/12 14:52:11 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signals(int action)
{

	// struct sigaction	sa_sig;

	signal(SIGTSTP, SIG_IGN);
	if (action == 1) // ctrl-C
	{}
	else if (action == 2) // ctrl-D
	{}
	else if (action == 3) // ctrl-\ 
	{}

}

void	exit_shell(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*str;

	if (ac != 1)
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	while (80085)
	{
		handle_signals(0);
	}
}
