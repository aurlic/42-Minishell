/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:57:41 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/22 10:16:59 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_return = 130;
	}
}

static void	sig_heredoc(int sig)
{
	write(1, "\n", 1);
	g_return = 130;
	(void) sig;
}

void	handle_signals(int action)
{
	struct sigaction	sig;

	signal(SIGTSTP, SIG_IGN);
	if (action == 0)
	{
		sig.sa_flags = SA_RESTART;
		sig.sa_handler = handler;
		sigemptyset(&sig.sa_mask);
		sigaction(SIGINT, &sig, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (action == 1)
	{
		sig.sa_flags = 0;
		sig.sa_handler = &sig_heredoc;
		sigemptyset(&sig.sa_mask);
		sigaction(SIGINT, &sig, NULL);
	}
}
