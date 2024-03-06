/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:57:41 by aurlic            #+#    #+#             */
/*   Updated: 2024/03/06 10:42:06 by marvin           ###   ########.fr       */
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

void	handle_signals(int action)
{
	struct sigaction	sig;

	signal(SIGTSTP, SIG_IGN);
	if (action == 0)
	{
		sig.sa_flags = SA_RESTART;
		sig.sa_handler = handler;
		sigaction(SIGINT, &sig, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (action == 1)
	{
		// IN CASE OF HEREDOC -> HANDLE CTRL D IN HERE DOC
	}
}
