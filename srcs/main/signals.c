/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: traccurt <traccurt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:57:41 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/14 11:26:41 by traccurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
// void	handle_signals(int action, void (*f)(int))

void	handle_signals(int action)
{
	struct sigaction	sig;

	// signal(SIGTSTP, SIG_IGN);
	if (action == 0)
	{
		sig.sa_flags = SA_RESTART;
		sig.sa_handler = handler;
		sigemptyset(&sig.sa_mask);
		sigaction(SIGINT, &sig, NULL);
		// signal(SIGQUIT, SIG_IGN);
	}
	if (action == 1)
	{
		sig.sa_flags = SA_RESTART;
		sig.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sig, NULL);
		// signal(SIGQUIT, SIG_IGN);
		// IN CASE OF HEREDOC -> HANDLE CTRL D IN HERE DOC
	}
}
